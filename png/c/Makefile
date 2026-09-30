CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS = -lz

all: png

png: png.c
	$(CC) $(CFLAGS) -o png png.c $(LDFLAGS)

clean:
	rm -f png

run: png
	./png test.png

.PHONY: clean run
