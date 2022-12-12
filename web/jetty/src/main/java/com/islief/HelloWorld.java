package com.islief;

import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.servlet.ServletException;
import java.io.IOException;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Connector;
import org.eclipse.jetty.server.ServerConnector;
import org.eclipse.jetty.server.handler.AbstractHandler;
import org.eclipse.jetty.server.HttpConnectionFactory;
import org.eclipse.jetty.util.thread.QueuedThreadPool;

// http://www.eclipse.org/jetty/documentation/jetty-11/programming-guide/index.html#creating-helloworld-class
public class HelloWorld extends AbstractHandler
{
    @Override
    public void handle(String target, Request jettyRequest, HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
    {
      response.setStatus(HttpServletResponse.SC_OK);
      if (!target.equals("/style.css")) {
        response.setContentType("text/html; charset=utf-8");
        response.getWriter().println("<html><head><link rel='stylesheet' type='text/css' href='/style.css' integrity='sha384-1cbX2JjXj8NgXojhuqrmQQ63tUP5/6uTUDNqiiXPW0PA3arKgYg6Ug9OEyt9kGhh' /></head><body><div id='main'>Hello, World! ... brought to you by Jetty</div></body></html>");
      } else {
        response.setContentType("text/css");
        response.getWriter().println("#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: blue;font-size: 40px; }");
      }

      jettyRequest.setHandled(true);
    }

    public static void main(String[] args) throws Exception
    {
        int port = 8080;
        if (args.length > 0) {port = Integer.parseInt(args[0]);}

        QueuedThreadPool threadPool = new QueuedThreadPool();
        threadPool.setName("server");
        Server server = new Server(threadPool);
        ServerConnector connector = new ServerConnector(server, 1, 1, new HttpConnectionFactory());
        connector.setPort(port);
        server.addConnector(connector);
        server.setHandler(new HelloWorld());
        server.start();
        server.join();
    }
}
