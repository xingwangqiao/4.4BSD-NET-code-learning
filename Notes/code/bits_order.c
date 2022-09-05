#include <stdio.h>
struct Test {
    union 
    {
        __uint16_t a;
        __uint8_t b[2];
    } un;
    
};
int main() {
    struct Test test;
    test.un.a = 0x0102;
    if(test.un.b[0] == 0x01) {
        printf("big-endian\n");
    } else if(test.un.b[0] == 0x02) {
        printf("little-endian\n");
    } else {
        printf("unknow\n");
    }
    return 0;
}