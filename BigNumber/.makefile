all: demo.o bignumber.o
	g++ -I./ demo.o bignumber.o -o demo.out
	./demo.out > log
demo.o: demo.cpp bignumber.h
	g++ -I./ -c demo.cpp -o demo.o
bignumber.o: bignumber.cc bignumber.h
	g++ -I./ -c bignumber.cc -o bignumber.o
bp: bignumber.cc bignumber.h
	cp bignumber.cc bignumber.h backup
