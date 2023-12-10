package com.example.boat_wifi_controller;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class Send extends Thread {
    private String send;
    private OutputStream outputStream;
    private  InputStream inputStream;
    private int str;
    private int port;
    private Socket so;

    public Send(Socket socket, int str) {
        so = socket;
        this.str = str;
    }

    @Override
    public void run() {
        try {
            inputStream = so.getInputStream();
            outputStream = so.getOutputStream();
            outputStream.write((str + "\n").getBytes("utf-8"));
            outputStream.flush();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }
}
