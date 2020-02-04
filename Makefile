CC = g++
SOURCE = cwave.cpp
PROGRAM = cwave

$(PROGRAM): $(SOURCE)
	$(CC) $(SOURCE) -o $(PROGRAM) -lm -std=c++11 -Wall -pedantic-errors

install: $(PROGRAM)
	install -s $(PROGRAM) /usr/local/bin