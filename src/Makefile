CFLAGS = -Wall -g -I. -I../include -I../gnulib/lib

# https://stackoverflow.com/questions/22551167/using-a-result-of-shells-find-as-a-target-in-a-makefile
sources = $(shell find . -maxdepth 1 -name '*.c')

all: $(sources:.c=.o)
	@echo $^

include $(sources:.c=.d)

# http://www.microhowto.info/howto/automatically_generate_makefile_dependencies.html
# generate dependencies
%.d: %.c
	@set -e; rm -f $@; \
	$(CC) -MM $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
