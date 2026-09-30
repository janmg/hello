package com.islief;

import java.io.*;
import java.net.*;
import java.util.*;

public class WebServerApp {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(8080);
        System.out.println("Server running on port 8080");
        while (true) {
            Socket socket = server.accept();
            BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            String line = in.readLine();
            if (line != null && line.contains("/style.css")) {
                out.println("HTTP/1.1 200 OK");
                out.println("Content-Type: text/css");
                out.println("Connection: close");
                out.println();
                out.println("#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #5382A1;font-size: 40px; }");
            } else {
                out.println("HTTP/1.1 200 OK");
                out.println("Content-Type: text/html; charset=utf-8");
                out.println("Connection: close");
                out.println();
                out.println("<html><head><link rel='stylesheet' type='text/css' href='/style.css' integrity='sha384-WDloaytqdWixSs7cY74Ziipj5mMrEeGChhqDrHvuYEJAYizXYFk6ST+mDxU3DByy' /></head><body><div id='main'>Hello, World! ... brought to you by Java SDK 21</div></body></html>");
            }

            out.flush();
            socket.close();
        }
    }
}