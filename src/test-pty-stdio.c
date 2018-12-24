#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int
main(){
  struct termios ts;

  if(tcgetattr(STDIN_FILENO, &ts))
  {
    perror("tcgetattr");
    exit(1);
  }

  printf("ttyname(STDIN_FILENO): %s\n", ttyname(STDIN_FILENO));
  printf("ptsname(STDIN_FILENO): %s\n", ptsname(STDIN_FILENO));

  printf("ttyname(STDOUT_FILENO): %s\n", ttyname(STDOUT_FILENO));
  printf("ptsname(STDOUT_FILENO): %s\n", ptsname(STDOUT_FILENO));

  // get the path to the slave
  char slavepath[64];
  if(ptsname_r(STDIN_FILENO, slavepath, sizeof(slavepath)) < 0)
  {
    perror("ptsname_r");
    exit(1);
  }
  printf("Using slavepath %s\n", slavepath);

  char slavepath2[64];
  if(ptsname_r(STDOUT_FILENO, slavepath2, sizeof(slavepath2)) < 0)
  {
    perror("ptsname_r");
    exit(1);
  }
  printf("Using slavepath2 %s\n", slavepath2);

  return 0;
}
