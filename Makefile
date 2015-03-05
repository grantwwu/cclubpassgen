CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -Wstrict-prototypes -O2
LIBRARYFLAGS=-lssl -lcrypto

test: passgen.c test.c
	$(CC) $(CFLAGS) passgen.c test.c -o passgentest -DDEBUG $(LIBRARYFLAGS)
