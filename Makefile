
CC=gcc
CFLAGS=-c -std=c99 -pedantic
LDFLAGS=-lSDL2
SOURCES=gameboy.c my_sdl.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=gameboy

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)

