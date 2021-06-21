FILE=problema2

TESTS = test1 test2 test3

all: $(FILE)

$(FILE).o: $(FILE).c
	cc -Wall -g -c $(FILE).c

$(FILE): $(FILE).o
	cc -Wall -o $(FILE) $(FILE).o


PHONY: test

test: $(FILE) $(TESTS)

$(TESTS): %: %.txt 
	./$(FILE) < $<

PHONY: clean
clean:
	rm $(FILE) $(FILE).o
