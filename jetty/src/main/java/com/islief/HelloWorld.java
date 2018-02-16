package com.islief;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.HttpConfiguration;
import org.eclipse.jetty.server.HttpConnectionFactory;
import org.eclipse.jetty.server.ServerConnector;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.eclipse.jetty.http2.server.HTTP2CServerConnectionFactory;

public class HelloWorld extends AbstractHandler
{
    @Override
    public void handle( String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response ) throws IOException, ServletException
    {
        response.setStatus(HttpServletResponse.SC_OK);
        response.setContentType("text/html; charset=utf-8");
        if (!target.equals("/style.css")) {
          response.setContentType("text/html; charset=utf-8");
          response.getWriter().println("<html><head><link rel='stylesheet' type='text/css' href='/style.css' integrity='sha384-1cbX2JjXj8NgXojhuqrmQQ63tUP5/6uTUDNqiiXPW0PA3arKgYg6Ug9OEyt9kGhh' /></head><body><div id='main'>Hello, World! ... brought to you by Jetty</div></body></html>");
        } else {
          response.setContentType("text/css; charset=utf-8");
          response.getWriter().println("#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: blue;font-size: 40px; }");
        }
        baseRequest.setHandled(true);
    }

    public static void main(String[] args) throws Exception
    {
        int port = 8080;
        if (args.length > 0) {port = new Integer(args[0]);}
        Server server = new Server();
        HttpConfiguration config = new HttpConfiguration();
        HttpConnectionFactory http1 = new HttpConnectionFactory(config);
        HTTP2CServerConnectionFactory http2c = new HTTP2CServerConnectionFactory(config); 
        ServerConnector connector = new ServerConnector(server, http1, http2c);
        connector.setPort(port);
        server.addConnector(connector);

        server.setHandler(new HelloWorld());
        server.start();
        // server.join();
    }
}

