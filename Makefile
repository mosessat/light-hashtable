CC=gcc
CFLAGS=-I.
LFLAGS=-L.
DEPS = hash.h
LIBNAME=lhash
LIBSUFFIX=lib
LIBPATH=/usr/local/lib
DLIBNAME=$(LIBSUFFIX)$(LIBNAME).so
SLIBNAME=$(LIBSUFFIX)$(LIBNAME).a
MACROVALUES=-D D_HASHSIZE=101

all: dll examples

dll: $(DLIBNAME) $(SLIBNAME)

$(DLIBNAME): hash.c
	$(CC) -shared -o $@ $^ -fPIC $(CFLAGS)

$(SLIBNAME): hash.o
	ar rcs $(SLIBNAME) $^

%.o: %.c $(DEPS)
	$(CC) $(MACROVALUES) -c -o $@ $< $(CFLAGS)

examples: examples/test.o
	$(CC) $(CFLAGS) $(LFLAGS) -l$(LIBNAME) -o examples/test.out $^

clean:
	rm hash.o $(SLIBNAME) $(DLIBNAME) examples/*.o examples/test.out
