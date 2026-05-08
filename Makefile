CC = gcc
CFLAGS = -Wall -Wextra -pedantic -O2
LDFLAGS = 
LDLIBS = 

# Source files
TAIL_SRC = tail.c cbuf.c
HTAB_SRC = htab_bucket_count.c htab_clear.c htab_erase.c htab_find.c \
           htab_for_each.c htab_free.c htab_hash_function.c \
           htab_init.c htab_lookup_add.c htab_size.c
MAXWORDCOUNT_SRC = maxwordcount.c

# Targets
all: tail maxwordcount maxwordcount-dynamic libhtab.a libhtab.so

# Programs
tail: $(TAIL_SRC)
	$(CC) $(CFLAGS) -o $@ $^

maxwordcount: $(MAXWORDCOUNT_SRC) libhtab.a
	$(CC) $(CFLAGS) -static -o $@ $(MAXWORDCOUNT_SRC) -L. -lhtab

maxwordcount-dynamic: $(MAXWORDCOUNT_SRC) libhtab.so
	$(CC) $(CFLAGS) -o $@ $(MAXWORDCOUNT_SRC) -L. -lhtab
	export LD_LIBRARY_PATH=.:$$LD_LIBRARY_PATH

# Libraries
libhtab.a: $(HTAB_SRC:.c=.o)
	ar rcs $@ $^

libhtab.so: $(HTAB_SRC:.c=.o)
	$(CC) -shared -fPIC -o $@ $^

# Pattern rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c -o $@ $<

# Clean
clean:
	rm -f *.o *.a *.so tail maxwordcount maxwordcount-dynamic

run: tail maxwordcount maxwordcount-dynamic
	seq 0 2 20 | shuf | ./tail
	seq 0 5 50 | shuf | ./maxwordcount
	export LD_LIBRARY_PATH="." && seq 0 10 100 | shuf | ./maxwordcount-dynamic

# Check
check: all run


.PHONY: all clean run check