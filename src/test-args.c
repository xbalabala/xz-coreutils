#include <stdio.h>
#include <unistd.h>

int
main (int argc, char **argv) {
  printf("optind: %d\n", optind);

  printf("argc: %d\n", argc);
  printf("argv: %p\n", argv);
  for(int i = 0; i < argc; i++) {
    printf("argv[%d]: %s\n", i, argv[i]);
  }

  return 0;
}

/*
$./build/test-args some one two

optind: 1
argc: 4
argv: 0x7ffd2bc24288
argv[0]: ./build/test-args
argv[1]: some
argv[2]: one
argv[3]: two
*/
