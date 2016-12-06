FLAGS= -g -std=c++11
COMP=g++
all: main

main: kdtree.o
	$(COMP) $(FLAGS) main.cpp -o main

test: test-out test-mem

%.o: %.cpp
	$(COMP) $(FLAGS) -o $@ -c $<

test-out: kdtree.o test.t.cpp
	@echo Testing Output...
	$(COMP) test.t.cpp -o test && ./test

test.n: test.n.cpp
	$(COMP) $(FLAGS) $< -o $@ 

test-mem:	main
	@echo Testing Memory...
	@[ `valgrind --leak-check=full ./main 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

clean:
	rm *.o main test
