CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -Wstrict-prototypes -O2
LIBRARYFLAGS=-lssl -lcrypto

test: passgen.c
	$(CC) $(CFLAGS) passgen.c -o passgentest -DDEBUG $(LIBRARYFLAGS)
