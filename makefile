CC = g++
CFLAGS = -g -Wall

default:	genstar

genstar:	main.o StarSystem.o StarData.o
	$(CC) -o GenStar2 main.o StarSystem.o StarData.o

main.o:
	$(CC) -c main.cpp

StarSystem.o:
	$(CC) -c StarSystem.cpp

StarData.o:
	$(CC) -c StarData.cpp

clean:
	$(RM) GenStar2 *.o *~