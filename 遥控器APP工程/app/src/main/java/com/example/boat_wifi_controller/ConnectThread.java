package com.example.boat_wifi_controller;


import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.io.OutputStream;
import java.io.InputStream;
import java.net.Socket;

public class ConnectThread extends Thread {
    //Socket msg = null;//定义socket
    private OutputStream out_ip=null;//定义输出流（ip）
    OutputStream outputStream=null;
    private InputStream inputStream;
    private StringBuffer stringBuffer;
    private String ip;
    private int port;
    private Receive receive;
//    private  MainActivity.Receive re;
    private String string;
    public Socket socket = null;
    public Handler mHandler;
    private Handler handlerSendMsgHandler;

    public ConnectThread(String ip, int port) {
        this.ip = ip;
        this.port = port;
        //this.re = re;

    }



    @Override
    public void run(){

        try {
            socket = new Socket(ip, port);
        } catch (IOException e) {
            e.printStackTrace();
        }

//        System.out.println(Thread.currentThread().getName() + ": Hello");
//        try {
//            inputStream = socket.getInputStream();
//            out_ip = socket.getOutputStream();
//            Log.v("AndroidChat","开始连接服务器："+ip+"/"+port);
//            sleep(1000);
//        }
//        catch (IOException | InterruptedException e) {
//            Log.v("AndroidChat","连接服务器失败"+e.getMessage());
//            e.printStackTrace();
//            return;
//        }
//        Log.v("AndroidChat","成功连接上服务器");
//
//        while(true) {
//            try {
//                inputStream = socket.getInputStream();
//                final byte[] buffer = new byte[1024];
//                final int len = inputStream.read(buffer);
//                System.out.println(new String(buffer, 0, len));
//                string = new String(buffer, 0, len);
//                re.setString(string);//将string放置到re.setString中
//
//                //System.out.println(new String(buffer, 0, len));
//            } catch (IOException e) {
//                e.printStackTrace();
//            }
//        }



    }
}


