CC = g++
FLAGS = -I./includes -c -o
SRCFILES := $(filter-out monolith.cpp,$(wildcard *.cpp))
OBJECTS := $(patsubst %.cpp,build/%.o,$(filter-out monolith.cpp, $(wildcard *.cpp)))

GoL: $(OBJECTS)
	$(CC) -o GoL $^ -lSDL2

build/%.o: %.cpp
	@echo Compiling $< into build/ dir
	$(CC) $(FLAGS) $@ $<

clean:
	rm objects/*
