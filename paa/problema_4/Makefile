FILE := main

TESTS := test1 test2 test3

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  CC=g++
else 
  CC=clang++
endif

all: $(FILE)

$(FILE).o: $(FILE).cc
	$(CC) -Wall -g -c $(FILE).cc

$(FILE): $(FILE).o
	$(CC) -Wall -o $(FILE) $(FILE).o


PHONY: test

test: $(FILE) $(TESTS)

$(TESTS): %: %.txt 
	./$(FILE) < $<

PHONY: clean
clean:
	rm $(FILE) $(FILE).o
