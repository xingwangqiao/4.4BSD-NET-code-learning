#include "common.h"

#include <errno.h>
#include <stdio.h>

size_t readn(int fd, void* bufptr, size_t size) {
    int readd = 0, n = 0;

    while(readd < size) {
        if((n = read(fd, bufptr, size-readd)) >= 0) {
            readd += n;
            bufptr += n;
        } else if(errno == EINTR) {
            continue;
        } else {
            perror("read error");
        }
    }

    return readd;
}

size_t readl(int fd, char* bufptr, size_t size) {
    int readd = 0, n = 0;
    char ch;
    while(readd < size) {
        if((n = read(fd, bufptr, 1)) >= 0) {
            ++ readd;
            ch = *(bufptr++);
            if(ch == '\0' || ch == '\n')
                break;
        } else if(errno == EINTR) {
            continue;
        } else {
            perror("read error");
        }
    }

    return readd;
}

size_t writen(int fd, void* bufptr, size_t size) {
    int writ = 0, n = 0;

    while(writ < size) {
        if((n = write(fd, bufptr, size-writ)) >= 0) {
            writ += n;
            bufptr += n;
        } else if(errno == EINTR) {
            continue;
        } else {
            perror("write error");
        }
    }

    return writ;
}

int max(int l, int r) {
    return l > r ? l : r;
}