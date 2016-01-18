all: bug clear

bug: archivation.o LZ77.o test.o nope.o 
	g++ archivation.o LZ77.o test.o nope.o -o test

archivation.o: archivation.cpp
	g++ -c archivation.cpp

LZ77.o: LZ77.cpp
	g++ -c LZ77.cpp

main.o: test.cpp
	g++ -c main.cpp

nope.o: nope.cpp
	g++ -c nope.cpp

clear: 
	del *.o