FLAGS= -g -std=c++11
COMP=g++
all: main

main: kdtree.o
	$(COMP) $(FLAGS) main.cpp -o main

%.o: %.cpp
	$(COMP) $(FLAGS) -o $@ -c $<

test: kdtree.o test.t.cpp
	$(COMP) test.t.cpp -o test && ./test

test.n: test.n.cpp
	$(COMP) $(FLAGS) $< -o $@ 

clean:
	rm *.o main test
