CC=gcc
CFLAGS=-std=c11
PROG=autobackup

autobackup: autobackup.c
	$(CC) -o $(PROG) autobackup.c src/*.c $(CFLAGS)

install:
	install -m 0755 autobackup /usr/local/bin
