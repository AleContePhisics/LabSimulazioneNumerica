CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: simulator.exe
simulator.exe : GenAlgorithm.o Simulator.o random.o
	$(CC) GenAlgorithm.o random.o Simulator.o -o simulator.exe $(AFLAGS)
Simulator.o : Simulator.cpp GenAlgorithm.h
	$(CC) -c Simulator.cpp -o Simulator.o $(CFLAGS)
system.o : GenAlgorithm.cpp GenAlgorithm.h random.h
	$(CC) -c GenAlgorithm.cpp -o GenAlgorithm.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o simulator.exe
remove:
	rm ../OUTPUT/*.*
	rm ../OUTPUT/CONFIG/*.*
