
CFLAGS=-I.\
			 -I/usr/include/x86_64-linux-gnu/ruby-2.1.0 \
			 -I/usr/include/ruby-2.1.0
LDFLAGS=-lruby-2.1
default: lib/libtelldus-core.so lib/telldus_state.so

lib/telldus_state.so: lib/libtelldus-core.so
	ln -sf libtelldus-core.so lib/telldus_state.so

lib/libtelldus-core.so: telldus-core.o
	gcc -shared $(LDFLAGS) telldus-core.o -o lib/libtelldus-core.so

telldus-core.o: telldus-core.c include/telldus-core.h
	cc -fPIC $(CFLAGS) -o telldus-core.o -c telldus-core.c

clean:
	rm -f lib/*.so
	rm -r *.o

