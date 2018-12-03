// https://docs.oracle.com/cd/E19253-01/816-4855/termsub15-14/index.html

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>

int
main() {
  int fdm, fds;
  char *slavename;
  extern char *ptsname();

  fdm = open("/dev/ptmx", O_RDWR);  /* open master */
  grantpt(fdm);                     /* change permission of slave */
  unlockpt(fdm);                    /* unlock slave */
  slavename = ptsname(fdm);         /* get name of slave */
  fds = open(slavename, O_RDWR);    /* open slave */
  // ioctl(fds, I_PUSH, "ptem");       /* push ptem */
  // ioctl(fds, I_PUSH, "ldterm");    /* push ldterm */

  printf("fdm: %d\n", fdm);
  printf("fds: %d\n", fds);
  printf("slavename: %s\n", slavename);
  char *ttyname_str = ttyname(fdm);
  printf("ttyname: %s\n", ttyname_str);
}

// output:
// vagrant@vagrant:/vagrant/xz-coreutils$ ./build/test-tty
// fdm: 3
// fds: 4
// slavename: /dev/pts/8
// ttyname: /dev/ptmx
