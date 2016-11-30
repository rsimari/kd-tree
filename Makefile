FLAGS= -g -std=c++11
all: main

main: kdtree.o
	g++ $(FLAGS) main.cpp -o main

%.o: %.cpp
	g++ $(FLAGS) -o $@ -c $<

clean:
	rm *.o main