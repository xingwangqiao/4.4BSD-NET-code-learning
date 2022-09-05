#include "common.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("usage: ./a.out <address>\n");
        return 1;
    }

    char* addr = argv[1];

    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    inet_pton(AF_INET, addr, &serv_addr.sin_addr);
    serv_addr.sin_port = htons(10086);
    
    int conn_fd;
    conn_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(conn_fd < 0) {
        perror("create socket error");
        return 1;
    }

    if((connect(conn_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        perror("connect server faild");
        return 1;
    }

    fd_set clt_set, read_set;
    FD_ZERO(&clt_set);
    FD_SET(conn_fd, &clt_set);
    FD_SET(STDIN_FILENO, &clt_set);
    FD_ZERO(&read_set);   
    while(1) {
        read_set = clt_set;
        int ret;
        write(STDOUT_FILENO, "input>>", 8);
        if((ret=select(conn_fd+1, &read_set, NULL, NULL, NULL)) == -1) {
            if(errno == EINTR)
                continue;
            else {
                perror("select error");
                break;
            }
        }
        char msgbuf[2048];
        size_t readd = 0;
        if(FD_ISSET(STDIN_FILENO, &read_set)) {
            readd = readl(STDIN_FILENO, msgbuf, sizeof(msgbuf));
            writen(conn_fd, msgbuf, readd);
        }

        if(FD_ISSET(conn_fd, &read_set)) {
            readd = readl(conn_fd, msgbuf, sizeof(msgbuf));
            writen(STDOUT_FILENO, msgbuf, readd);
        }
    }

    return 0;
}