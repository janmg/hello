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
    public void handle( String target,
                        Request baseRequest,
                        HttpServletRequest request,
                        HttpServletResponse response ) throws IOException,
                                                      ServletException
    {
        response.setContentType("text/html; charset=utf-8");
        response.setStatus(HttpServletResponse.SC_OK);
        response.getWriter().println("<html><body><div style='position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Arial, Helvetica, sans-serif;color: blue;font-size: 40px;'>Hello, World! ... brought to you by Jetty</div></body></html>");
        baseRequest.setHandled(true);
    }

    public static void main(String[] args) throws Exception
    {
        Server server = new Server();
        HttpConfiguration config = new HttpConfiguration();
        HttpConnectionFactory http1 = new HttpConnectionFactory(config);
        HTTP2CServerConnectionFactory http2c = new HTTP2CServerConnectionFactory(config); 
        ServerConnector connector = new ServerConnector(server, http1, http2c);
        connector.setPort(8003);
        server.addConnector(connector);

        server.setHandler(new HelloWorld());
        server.start();
        // server.join();
    }
}

