CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pthread -Wvla
GCH = Matrix.hpp.gch
HEADERS = AdditionException.h TraceException.h MatrixAllocException.h
MatrixAssignmentException.h MultiplicationException.h MoveException.h
SubtractionException.h 
TARGET = Matrix
FILES = $(HEADERS) README Makefile
TAR = ex3.tar

.DEFAULT_GOAL := $(TARGET)

.PHONY: default all clean tar $(TARGET)

$(TARGET): $(HEADERS)
	$(CC) -c $(CFLAGS) Matrix.hpp 

all: $(TARGET) tar

tar: $(FILES)
	tar cvf $(TAR) $(FILES)

clean:
	rm -f  $(GCH) $(TAR)
