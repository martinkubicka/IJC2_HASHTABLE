CC=gcc
CFLAGS= -std=c11 -pedantic -Wall -Wextra -fPIC
OBJFILES=htab_init.o htab_hash_function.o htab_size.o htab_bucket_count.o htab_resize.o htab_lookup_add.o htab_find.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o 

all: tail libhtab.a libhtab.so wordcount-dynamic wordcount 

tail: tail.o
	$(CC) $(CFLAGS) tail.o -o tail

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c -o tail.o

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) -o $@ wordcount.o io.o -L. -lhtab

wordcount: wordcount.o io.o libhtab.a
	$(CC) -static -o $@ wordcount.o io.o -L. -lhtab

libhtab.so: $(OBJFILES)
	$(CC) $(CFLAGS) -shared -o $@ $^

libhtab.a: $(OBJFILES)
	ar crs $@ $^

clean:
	rm *.o tail wordcount wordcount-dynamic libhtab.a libhtab.so

