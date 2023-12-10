package com.example.boat_wifi_controller;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;

public class MainActivity extends AppCompatActivity {
    private InputStream inputStream;
    private String tem_str;
    private String hum_str;
    private String dis_str;
    private String lon_str;
    private String lat_str;
    private static TextView tem;
    private static TextView hum;
    private static TextView dis;
    private static TextView lon;
    private static TextView lat;
    private ImageView left;
    private ImageView right;
    private ImageView forward1;
    private ImageView forward2;
    private ImageView back;

    private Button stop;
    private Button link;
    private Button relink;

    private String host = "tcp://192.168.4.1:333";
    private String userName = "android";
    private String passWord = "android";
    private String mqtt_id = "controller";
    private String mqtt_sub_topic = "565402462"; //为了保证你不受到别人的消息  哈哈

    private String mqtt_pub_topic = "565402462_PC"; //为了保证你不受到别人的消息  哈哈  自己QQ好后面加 _PC
    private ScheduledExecutorService scheduler;
    private MqttClient client;
    private MqttConnectOptions options;


    private Message message = new Message();
    private ConnectThread ct;
    private Send send;
    //static Receive re = new Receive();
    private OutputStream outputStream;
    private Socket socket = null;
    private MotionEvent event;
    static boolean flag = false;
    private char conect_flag = 0 ;
    @SuppressLint("HandlerLeak")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        tem = findViewById(R.id.tem);
        hum = findViewById(R.id.hum);
        dis = findViewById(R.id.dis);
        lon = findViewById(R.id.lon);
        lat = findViewById(R.id.lat);


        link = findViewById(R.id.link);
        link.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(conect_flag == 0 ){
//                    ct = new ConnectThread("192.168.4.1",333,re);//创建一个线程来处理消息的收发
//                    ct.start();//启动连接接收线程
//                    conect_flag = 1;
                    new Thread() {
                        @Override
                        public void run() {
                            try {
                                socket = new Socket("192.168.4.1", 333);
                            } catch (IOException e) {
                                throw new RuntimeException(e);
                            }
                            conect_flag = 1;
                            while(true) {
                                try {
                                    inputStream = socket.getInputStream();
//                                    byte[] test = new byte[1];
//                                    inputStream.read(test);
//                                    if(test[0] != '\n'){
//                                        continue;
//                                    }
                                    byte[] buffer = new byte[32];
                                    int len = inputStream.read(buffer);
                                    if(buffer[0] == '\n' && buffer[31] == '\r') {
//                                        System.out.println(buffer[9]);
                                        //System.out.println(new String(buffer, 0, len));
                                        hum_str = new String(buffer, 1, 2);
                                        tem_str = new String(buffer, 3, 2);
                                        int count = 0;
                                        while( buffer[5+count] == '0') count ++;
                                        dis_str = new String(buffer, 5+count, 4-count);
                                        if( buffer[17] == 0 ){
                                            lon_str = "无信号";
                                            lat_str = "无信号";
                                        }else {
                                            lon_str = new String(buffer, 9, 10);
                                            lat_str = new String(buffer, 20, 11);
                                        }
//                                        tem_str = new String(buffer, 3, 2);
//                                        hum_str = new String(buffer, 1, 2);
                                        runOnUiThread(new Runnable() {
                                            public void run() {
                                                //System.out.println(len);
                                                //System.out.println(lon_str);
                                                tem.setText(tem_str);
                                                hum.setText(hum_str);
                                                dis.setText(dis_str);
                                                lon.setText(lon_str);
                                                lat.setText(lat_str);
                                            }
                                        });
                                    }
                                    //inputStream.close();
                                    //System.out.println(new String(buffer, 0, len));
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                            //重点在这里
                        }
                    }.start();
                    Toast.makeText(MainActivity.this, "连接成功", Toast.LENGTH_SHORT).show();
                }
                else
                    Toast.makeText(MainActivity.this,"已连接" ,Toast.LENGTH_SHORT).show();
            }
        });

        left = findViewById(R.id.left);
        left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if( conect_flag == 1) {
                    if (event.getAction() == MotionEvent.ACTION_DOWN) {
                        send = new Send(socket, 0x01);
                        send.start();
                    }
                    if (event.getAction() == MotionEvent.ACTION_UP) {
                        send = new Send(socket, 0x00);
                        send.start();
                    }
                }
                else
                    Toast.makeText(MainActivity.this,"未连接" ,Toast.LENGTH_SHORT).show();
                return true;
            }
        });

        right = findViewById(R.id.right);
        right.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                if( conect_flag == 1) {
                    if (event.getAction() == MotionEvent.ACTION_DOWN) {
                        send = new Send(socket, 0x02);
                        send.start();
                    }
                    if (event.getAction() == MotionEvent.ACTION_UP) {
                        send = new Send(socket, 0x00);
                        send.start();
                    }
                }
                else
                    Toast.makeText(MainActivity.this,"未连接" ,Toast.LENGTH_SHORT).show();
                return true;
            }
        });

        forward1 = findViewById(R.id.forward1);
        forward1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if( conect_flag == 1) {
                    send = new Send(socket,0x03 );
                    send.start();
                }
                else
                    Toast.makeText(MainActivity.this,"未连接" ,Toast.LENGTH_SHORT).show();
            }
        });

        forward2 = findViewById(R.id.forward2);
        forward2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if( conect_flag == 1) {
                    send = new Send(socket,0x04 );
                    send.start();
                }
                else
                    Toast.makeText(MainActivity.this,"未连接" ,Toast.LENGTH_SHORT).show();
            }
        });

        back = findViewById(R.id.back);
        back.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if( conect_flag == 1) {
                    send = new Send(socket,0x05 );
                    send.start();
                }
                else
                    Toast.makeText(MainActivity.this,"未连接" ,Toast.LENGTH_SHORT).show();
            }
        });

        stop = findViewById(R.id.stop);
        stop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if( conect_flag == 1) {
                    send = new Send(socket,0x06 );
                    send.start();
                }
                else
                    Toast.makeText(MainActivity.this,"未连接" ,Toast.LENGTH_SHORT).show();
            }
        });

        relink = findViewById(R.id.relink);
        relink
                .setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if( conect_flag == 1) {
                    try {
                        socket.close();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                    conect_flag = 0;
                }
                else
                    Toast.makeText(MainActivity.this,"未连接" ,Toast.LENGTH_SHORT).show();
            }
        });

    }

//    static class Receive{
//        private String string;//声明一个数组string
//        public String getString(){
//            return string;//可以给string设置初值
//        }
//        public void setString(String s){
//            this.string = s;//用来接收其他线程的数据
//        }
//    }
//
//    public static void callback(){
//        //System.out.println(re.getString());
//        flag = false;
//        //tem.setText(re.getString());//将接收线程过来显示在接收区
//    }




}