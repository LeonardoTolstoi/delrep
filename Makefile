install: exe clean
	cp delrep /usr/local/bin/
	rm delrep

exe: main lib
	g++ delrep1.o delrep2.o -o delrep

main: main.cpp
	g++ -c main.cpp -o delrep1.o

lib: delrep.h delrep.cpp
	g++ -c delrep.cpp -o delrep2.o

clean:
	-rm delrep1.o delrep2.o 2>/dev/null

cleanall:
	-rm delrep1.o delrep2.o delrep debugfile.txt 2>/dev/null

