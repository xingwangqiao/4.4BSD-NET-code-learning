#include "common.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/select.h>

int add_connection(int* fds, int* cur_size, int new_fd, int max_size) {
    if(*cur_size >= max_size)
        return -1;
    *(fds + *cur_size++) = new_fd;
    return 0;
} 

int delete_connection(int* fds, int* cur_size, int fd) {
    int i = 0;
    int *del = fds, *end = fds + *cur_size;
    for(; i<*cur_size; ++i) {
        if(*del == fd) {
            break;
        }
        ++del;
    }
    if(del == end)
        return -1;
    if(del != end-1)
        *del = *(end-1);
    --*cur_size;
    return 0;
}

int main(int argc, char** argv) {
    int max_fd = -1, listen_fd, conn_fd[100], conn_fd_num = 0;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
        if(listen_fd < 0) {
        perror("cant create socket");
        exit(1);
    }
    max_fd = max(max_fd, listen_fd);

    socklen_t serv_len = sizeof(struct sockaddr_in), clt_len;
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, serv_len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(10086);

    if(bind(listen_fd, (struct sockaddr*)&serv_addr, serv_len) == -1) {
        perror("bind socket error");
        exit(1);
    }

    if(listen(listen_fd, 5) == -1) {
        perror("listen socket error");
        exit(1);
    }

    fd_set srv_set, read_set;
    FD_ZERO(&srv_set);
    FD_SET(listen_fd, &srv_set);
    FD_ZERO(&read_set);
    while(1) {
        read_set = srv_set;
        //printf("wait connecton or user's msg\n");
        //printf("current conn_cur is %d, max_fd is %d\n", conn_fd_num, max_fd);
        if(select(max_fd+1, &read_set, NULL, NULL, NULL) == -1) {
            if(errno == EINTR)
                continue;
            else {
                perror("select have error");
                break;
            }
        }

        if(FD_ISSET(listen_fd, &read_set)) {
            // process new connection
            struct sockaddr_in clt_addr;
            socklen_t clt_len;
            int new_fd = accept(listen_fd, (struct sockaddr*)&clt_addr, &clt_len);
            if(new_fd < 0) {
                if(errno == EINTR)
                    continue;
                else {
                    
                    exit(1);
                }
            }
            add_connection(conn_fd, &conn_fd_num, new_fd, 100);
            FD_SET(new_fd, &srv_set);
            max_fd = max(max_fd, new_fd);
        }
        
        int i = 0;
        for(; i<conn_fd_num; ++i) {
            // process each connection
            char msgbuf[2048];
            int msglen = 0;
            int readd = 0;
            if(FD_ISSET(conn_fd[i], &read_set)) {
                readd = readl(conn_fd[i], msgbuf, 2048);
                writen(conn_fd[i], msgbuf, readd);
            }
        }
    }
    close(listen_fd);
    return 0;
}