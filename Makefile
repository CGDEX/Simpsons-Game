CFLAGS=-Wall -g
FICHEIROS=cgi.h estado.c estado.h exemplo.c Makefile

install: exemplo
	sudo cp exemplo /usr/lib/cgi-bin
	sudo cp -R images /var/www/html
	touch install

exemplo: exemplo.o estado.o
	cc -o exemplo exemplo.o estado.o

exemplo.zip: $(FICHEIROS)
	zip -9 exemplo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o exemplo Doxyfile latex html install

estado.o: estado.c estado.h
exemplo.o: exemplo.c cgi.h estado.h
