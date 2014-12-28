
CC = g++
CFLAG = -g -w -std=c++0x -c
FLAG = -g -w -std=c++0x

SRCMONITOR = monitor.cpp
SRCPETRI = petri.cpp

LIB_MON = monitor.o
LIB_PET = petri.o

all:
	$(CC) $(CFLAG) $(SRCMONITOR)
	$(CC) $(CFLAG) $(SRCPETRI)
	$(CC) $(FLAG) $(LIB_PET) $(LIB_MON) main.cpp -o mon

clean: rm *.o
