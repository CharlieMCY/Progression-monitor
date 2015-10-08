
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
	cp safety_mon normal/traces5/
	cp safety_mon dataset/traces2/
	cp safety_mon bernoulli/traces2/
	cp safety_mon binomial/traces2/
	cp safety_mon geometric/traces2/
	cp safety_mon lognormal/traces2/
	cp safety_mon discrete/traces2/
	cp safety_mon negative_binomial/traces2/
	cp safety_mon poisson/traces2/
	cp safety_mon uniform/traces3/
	cp mon normal/traces5/
	cp mon dataset/traces2/
	cp mon bernoulli/traces2/
	cp mon binomial/traces2/
	cp mon geometric/traces2/
	cp mon lognormal/traces2/
	cp mon discrete/traces2/
	cp mon negative_binomial/traces2/
	cp mon poisson/traces2/
	cp mon uniform/traces3/


clean: rm *.o
