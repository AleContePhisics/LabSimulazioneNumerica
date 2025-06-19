CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: simulator.exe
simulator.exe : system.o Simulator.o random.o
	$(CC) system.o random.o Simulator.o -o simulator.exe $(AFLAGS)
Simulator.o : Simulator.cpp system.h
	$(CC) -c Simulator.cpp -o Simulator.o $(CFLAGS)
system.o : system.cpp system.h random.h
	$(CC) -c system.cpp -o system.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o simulator.exe
remove:
	rm ../OUTPUT/*.*
	rm ../OUTPUT/CONFIG/*.*
