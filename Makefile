CC = g++
LDFLAGS = -std=c++11 -O3 -lm
SOURCES = solver.cpp stamp.cpp parser.cpp main.cpp
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = Project2
INCLUDES = solver.h stamp.h parser.h

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o:  %.c  ${INCLUDES}
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o *.gch $(EXECUTABLE)
