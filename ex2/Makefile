CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
HEADERS = FileReader.h Parameters.h LyricalSong.h InstrumentalSong.h SortHelper.h Song.h
SOURCES = $(HEADERS:.h=.cpp) MIR.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = MIR
FILES =  $(SOURCES) $(HEADERS) README Makefile
TAR = ex2.tar

.DEFAULT_GOAL := $(TARGET)

.PHONY: default all clean tar

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

all: $(TARGET) tar

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $<

tar: $(FILES)
	tar cvf $(TAR) $(FILES)

clean:
	rm -f *.o $(TARGET) $(TAR)
