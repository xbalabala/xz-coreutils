#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

# define ZERO_BYTE_TRANSFER_ERRNO 0

size_t
full_write (int fd, const void *buf, size_t count)
{
  size_t total = 0;
  const char *ptr = (const char *) buf;

  while (count > 0)
  {
    size_t n_rw = write(fd, ptr, count);
    if (n_rw == (size_t) -1)
      break;
    if (n_rw == 0)
    {
      errno = ZERO_BYTE_TRANSFER_ERRNO;
      break;
    }
    total += n_rw;
    ptr += n_rw;
    count -= n_rw;
  }

  return total;
}

static bool
simple_cat (
     /* Pointer to the buffer, used by reads and writes.  */
     char *buf,

     /* Number of characters preferably read or written by each read and write
        call.  */
     size_t bufsize)
{
  /* Actual number of characters read, and therefore written.  */
  size_t n_read;

  /* Loop until the end of the file.  */

  while (true)
  {
    /* Read a block of input.  */
    n_read = read (STDIN_FILENO, buf, bufsize);

    if (n_read == -1)
      printf("read error"), exit(EXIT_FAILURE);

    /* End of this file?  */
    if (n_read == 0)
      return true;

    /* Write this block out.  */
    {
      /* The following is ok, since we know that 0 < n_read.  */
      size_t n = n_read;
      if (full_write (STDOUT_FILENO, buf, n) != n)
        printf("write error"), exit(EXIT_FAILURE);
    }
  }
}

int
main () {
  char *inbuf;
  inbuf = malloc((size_t) 128 * 1024);
  simple_cat(inbuf, 128 * 1024);
}
