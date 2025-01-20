CC=clang++
CFLAGS=-Wall -g -std=c++17 #-fsanitize=address
LDFLAGS=#-fsanitize=address
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
