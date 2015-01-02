
CC = g++
CFLAG = -g -w -std=c++0x -c
FLAG = -g -w -std=c++0x

SRCMONITOR = monitor.cpp
SRCPETRI = petri.cpp
SRCSAFETYMONITOR = safety_monitor.cpp
SRCSAFETYPETRI = safety_petri.cpp

LIB_MON = monitor.o
LIB_PET = petri.o
LIB_SAFETY_MON = safety_monitor.o
LIB_SAFETY_PET = safety_petri.o

all:
	$(CC) $(CFLAG) $(SRCMONITOR)
	$(CC) $(CFLAG) $(SRCPETRI)
	$(CC) $(CFLAG) $(SRCSAFETYMONITOR)
	$(CC) $(CFLAG) $(SRCSAFETYPETRI)
	$(CC) $(FLAG) $(LIB_PET) $(LIB_MON) main.cpp -o mon
	$(CC) $(FLAG) $(LIB_SAFETY_PET) $(LIB_SAFETY_MON) main.cpp -o safety_mon

clean: rm *.o
