CC = g++
CFLAGS = -Wall -O3 --std=c++11

es1.2.exe : es1.2.o random.o
	$(CC) random.o es1.2.o -o es1.2.exe
es1.2.o : es1.2.cpp
	$(CC) -c es1.2.cpp -o es1.2.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o es1.2.exe seed.out
