all: bintac

bintac: bintac.o Makefile
	$(CC) $(LDFLAGS) $< -o $@

bintac.o: bintac.c Makefile
	$(CC) -std=c99 -Wall -pipe $(CFLAGS) -c $< -o $@

clean:
	rm -f bintac bintac.o
