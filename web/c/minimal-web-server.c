// https://github.com/nir9/welcome/blob/master/lnx/minimalist-web-server/server.c
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <netinet/in.h>

void main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, 0x901f, 0};
    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bind(s, (struct sockaddr *)&addr, sizeof(addr));
    listen(s, 10);

    char buffer[256] = {0};
    while (1) {
        int client_fd = accept(s, 0, 0);
        recv(client_fd, buffer, 256, 0);

        char* f = buffer + 5;
        *strchr(f, ' ') = 0;
        
        if (strcmp(buffer + 4, "/style.css") == 0) {
            const char* css = "#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #00ADD8;font-size: 40px; }";
            char response[512];
            snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\nContent-Length: %zd\r\nConnection: close\r\n\r\n%s",
                strlen(css), css);
            send(client_fd, response, strlen(response), 0);
        } else {
            const char* html = "<html><head><style>#main { position:absolute;top:50%;left:0;margin-top:-50px;right:0;text-align: center;font-family: Lato;color: #00ADD8;font-size: 40px; }</style></head><body><div id='main'>Hello, World! ... brought to you by C</div></body></html>";
            char response[512];
            snprintf(response, sizeof(response),
                "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: %zd\r\nConnection: close\r\n\r\n%s",
                strlen(html), html);
            send(client_fd, response, strlen(response), 0);
        }
        close(client_fd);
        memset(buffer, 0, 256);
    }
    close(s);
}