// https://ipv4.google.com/search?q=%E6%8C%87%E9%92%88%E5%AF%B9%E9%BD%90
// https://www.cnblogs.com/clover-toeic/p/3853132.html

#include <stdio.h>
#include <unistd.h>

int
main(void) {
    unsigned int i = 0x12345678;

    unsigned char *p = (unsigned char *)&i;
    *p = 0xff;
    unsigned short *p1 = (unsigned short *)(p+1);
    *p1 = 0xffff;

    printf("getpagesize(): %d\n", getpagesize());

    unsigned int alignment_value = 4u;

    printf("address %p, v %d, sizeof v %ld, sizeof p %ld, %ld\n",
        p, *p, sizeof(*p), sizeof(p), ((size_t)p % alignment_value));
    printf("address %p, v %d, sizeof v %ld, sizeof p %ld, %ld\n",
        p1, *p1, sizeof(*p1), sizeof(p1), ((size_t)p1 % alignment_value));

    return 0;
}

/*
output:

getpagesize(): 4096
address 0x7ffeea9f4458, v 255, sizeof v 1, sizeof p 8, 0
address 0x7ffeea9f4459, v 65535, sizeof v 2, sizeof p 8, 1
*/
