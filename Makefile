CFLAGS = -Wall -g -O0 -I. -I./include
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
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-stpcpy src/test-stpcpy.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-read-write src/test-read-write.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-getdents src/test-getdents.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-strsep src/test-strsep.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-va-list src/test-va-list.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-stat src/test-stat.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-static src/test-static.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-tty src/test-tty.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-pty-master src/test-pty-master.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-pty-slave src/test-pty-slave.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/test-pty-stdio src/test-pty-stdio.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/ttyecho src/ttyecho.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/mypty src/mypty.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/mypty2 src/mypty2.o
	gcc $(CFLAGS) -o $(BUILD_DIR)/mypty3 src/mypty3.o

clean:
	find . -name '*.[od]' -print0 | xargs -0 -r rm -v
	rm -rf -v $(BUILD_DIR)/*

directories:
	mkdir -p build

.PHONY: directories build clean all
