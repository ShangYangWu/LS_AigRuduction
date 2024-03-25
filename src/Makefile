CC=g++
FLAGS=-O3 -Wall -Wextra
SOURCES=main.cpp cmd_producer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=arg_parser.hpp cmd_producer.hpp
EXECUTABLE=pa2.out

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

.cpp.o: $(HEADERS)
	$(CC) $(FLAGS) $< -c -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)