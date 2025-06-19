CC = g++
CFLAGS = -O3 --std=c++11
AFLAGS = -larmadillo
all: simulator.exe
simulator.exe : system.o simulator.o particle.o random.o
	$(CC) system.o particle.o random.o simulator.o -o simulator.exe $(AFLAGS)
simulator.o : simulator.cpp system.h particle.h
	$(CC) -c simulator.cpp -o simulator.o $(CFLAGS)
system.o : system.cpp system.h random.h particle.h
	$(CC) -c system.cpp -o system.o $(CFLAGS)
particle.o : particle.cpp particle.h
	$(CC) -c particle.cpp -o particle.o $(CFLAGS)
random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
clean :
	rm *.o simulator.exe
remove:
	rm ../OUTPUT/*.*
	rm ../OUTPUT/CONFIG/*.*
