#include <unistd.h>

size_t readn(int fd, void* bufptr, size_t size);

size_t readl(int fd, char* bufptr, size_t size);

size_t writen(int fd, void* bufptr, size_t size);

int max(int l, int r);