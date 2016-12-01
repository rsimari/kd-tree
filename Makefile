FLAGS= -g -std=c++11
COMP=g++
all: main

main: kdtree.o
	$(COMP) $(FLAGS) main.cpp -o main

%.o: %.cpp
	$(COMP) $(FLAGS) -o $@ -c $<

test:
	$(COMP) test.t.cpp -o test && ./test

clean:
	rm *.o main test