//例子介绍：8266作为WiFiServer端，打开TCP调试助手，模拟TCP Client的请求

#include <ESP8266WiFi.h>
  
const char* AP_ID = "Remote_Control_Boat";
const char* PASSWORD = "123456789";
#define MAX_SRV_CLIENTS 2  //做多多少个客户端可以连接

WiFiServer server(333);    //创建server 端口号是6666

WiFiClient serverClients[MAX_SRV_CLIENTS];   //定义最多多少个client可以连接本server(一般不要超过4个)
 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_ID,PASSWORD);
  server.begin();  //启动server
  server.setNoDelay(true);//关闭小包合并包功能，不会延时发送数据
 
}
 
void loop() {
  uint8_t i;
  
  if (server.hasClient()) {  //判断是否有新的client请求进来
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      
      //释放旧无效或者断开的client
      if (!serverClients[i] || !serverClients[i].connected()) {
        if (!serverClients[i]) {
          //serverClients[i]    判断指定序号的客户端是否有效
          serverClients[i].stop();  //停止指定客户端的连接
        }
        serverClients[i] = server.available();//分配最新的client
        break; //跳出一层for循环
      }
    }
    
    //当达到最大连接数 无法释放无效的client，需要拒绝连接
    if (i == MAX_SRV_CLIENTS) {
      WiFiClient client = server.available();
      client.stop();
    }
  }

  
  //检测client发过来的数据
  for (i = 0; i < MAX_SRV_CLIENTS; i++) {
    if (serverClients[i] && serverClients[i].connected()) {
      if (serverClients[i].available()) {
        while (serverClients[i].available()) {
          Serial.write(serverClients[i].read());
        }
      }
    }
  }
 
  if (Serial.available()) {
    //把串口调试器发过来的数据 发送给client
    size_t len = Serial.available();  //返回可读数据的长度
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    //push UART data to all connected telnet clients
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      if (serverClients[i] && serverClients[i].connected()) {
        serverClients[i].write(sbuf, len);//向客户端发送数据
        delay(1);
      }
    }
  }
}
