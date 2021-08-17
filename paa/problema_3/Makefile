FILE=problema3
CC=c++
FLAGS=-Wall -g
TESTS=test1 test2 test3

all: $(FILE)

$(FILE).o: $(FILE).cc
	$(CC) $(FLAGS) -c $<

$(FILE): $(FILE).o
	$(CC) $(FLAGS) -o $@ $<

PHONY: clean
clean:
	rm problema3 problema3.o

PHONY: test
test: $(FILE) $(TESTS)

$(TESTS): %: %.txt 
	./$(FILE) < $<
