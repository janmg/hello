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
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
            out.println("<html><body><h1>Hello, World!</h1></body></html>");

            if (!target.equals("/style.css")) {
                response.setContentType("text/html; charset=utf-8");
                response.getWriter().println(
                        "<html><head><link rel='stylesheet' type='text/css' href='/style.css' integrity='sha384-1cbX2JjXj8NgXojhuqrmQQ63tUP5/6uTUDNqiiXPW0PA3arKgYg6Ug9OEyt9kGhh' /></head><body><div id='main'>Hello, World! ... brought to you by Java SDK 21</div></body></html>");
            } else {
                response.setContentType("text/css");
                response.getWriter().println(
                        "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: green;font-size: 40px; }");

                socket.close();
            }
        }
    }
}