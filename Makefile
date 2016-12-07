FLAGS= -g -std=c++11
COMP=g++
all: main

main: kdtree.o nearest
	$(COMP) $(FLAGS) main.cpp -o main

test: test-out test-mem measure

%.o: %.cpp
	$(COMP) $(FLAGS) -o $@ -c $<

test-out: kdtree.o test.t.cpp
	@echo Testing Output...
	$(COMP) $(FLAGS) test.t.cpp -o test && ./test

nearest: nearest.cpp
	$(COMP) $(FLAGS) $< -o $@ 

test-mem:	main
	@echo Testing Memory...
	@[ `valgrind --leak-check=full ./main 2>&1 | grep ERROR | awk '{print $$4}'` = 0 ]

measure: main
	$(COMP) $(FLAGS) measure.cpp -o measure && ./measure ./main

clean:
	rm *.o main test
