PREFIX?=/usr
PREFIX_INSTALL?=/usr/local
CFLAGS=-g -Wall -I${PREFIX}/include/apr-1 -I${PREFIX}/apr/include/apr-util-1
LDFLAGS=-L${PREFIX}/lib -lapr-1 -pthread -laprutil-1

all:	devpkg

devpkg:	bstrlib.o db.o shell.o commands.o

install: all
	install -d $(DESTDIR)/$(PREFIX_INSTALL)/bin/
	install devpkg -m 4755 -o root $(DESTDIR)/$(PREFIX_INSTALL)/bin/

clean:
	rm -f *.o devpkg
	rm -f devpkg
	rm -rf *.dSYM

