#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int
main(){
  char buf[1024];
  int n_read;

  int f = open("Makefile", O_RDONLY);

  while ((n_read = read(f, buf, sizeof(buf))) > 0)
    write(1, buf, n_read);
}
