CFLAGS = -Wall -g -O0 -I. -I./include -I./gnulib/lib
BUILD_DIR = ./build

all: directories build

build-o:
	make -C src

build: build-o
	gcc $(CFLAGS) -o $(BUILD_DIR)/cat src/cat.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-align src/test-align.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-args src/test-args.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-next-line-num src/test-next-line-num.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-ls src/test-ls.o

clean:
	find . -name '*.[od]' -print0 | xargs -0 -r rm -v
	rm -rf -v $(BUILD_DIR)/*

directories:
	mkdir -p build

.PHONY: directories build clean all
