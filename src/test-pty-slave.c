// https://stackoverflow.com/questions/23459520/how-to-read-write-to-linux-pseudoterminals-using-separate-processes-but-without

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int
main(int argc, char* argv[])
{
  int fd = open("/dev/pts/8", O_RDWR | O_NOCTTY);
  if(fd < 0)
  {
    perror("open");
    exit(1);
  }

  struct termios ts;

  if(tcgetattr(fd, &ts))
  {
    perror("tcgetattr");
    exit(1);
  }

  cfmakeraw(&ts);
  tcsetattr(fd, TCSANOW, &ts);

  char bufout = 'A';
  char bufin;

  int c;
  while(1)
  {
    if(bufout == 'A') bufout = 'B';
    else if(bufout == 'B') bufout = 'A';
    printf("writing %c\n", bufout);
    c = write(fd, &bufout, 1);
    if(c == -1) break;

    printf("reading\n");
    c = read(fd, &bufin, 1);
    printf("read %i bytes: %c\n", c, bufin);
    if(c == -1) break;

    sleep(1);
  }

  close(fd);
  return 0;
}
