CFLAGS = -Wall -g -O0 -I.

# https://stackoverflow.com/questions/22551167/using-a-result-of-shells-find-as-a-target-in-a-makefile
sources = $(shell find . -maxdepth 1 -name '*.c')

all: $(sources:.c=.o)
	@echo $^

%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
