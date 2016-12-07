README.md

KD-Tree Event Recommendation Algorithm
John Joyce & Robert Simari

Overview:
The heart of our project consists of a kd_tree, with supported functionality such as insertion, search, nearest neighbor, and range search. The goal of the application is to generate a recommendation based on an target event using a kd-tree built using events retrieved from the Ticket Evolution API. To achieve the latter, we wrote a node.js app that consists of a 'TEvoWebService' model which is used to retrieve events from the Ticket Evolution API, an 'Event' model used to represent the event data retrieved from the API, and an 'AlgorithmController' that creates a persistent connection to our C++ 'nearest' program, initially passing it the event data (6000+ events) needed to generate a 3D KD-tree using the event date, popularity, and category parameters. After doing so, the controller is able to pass single events to the C++ program in the form of a comma separated line. The C++ program awaits such input, performing a nearest neighbor search using the tree it has previously built and the passed in line as the node of interest.  It subsequently outputs the event id of the nearest neighbor found, which is used as our recommended event. The instance of 'AlgorithmController' simply passes the event to the C++ program and catches its output, printing the corresponding event data in the terminal. The 'app.js' file is used as our node.js driver. A demonstration of this functionality can be seen by performing 'make' in the root directory, navigating to the 'node' directory, and running 'node app.js'. The output will specify both the target event used during the nearest neighbor search and the result, or recommended event.    


KD_TREE:
	To simulate building a balanced kd_tree, printing it in order, performing a nearest neighbor search and range search, simply 'make' and run ./main.
TESTS:
	To perform unit tests, memory checks, and measure the execution time/memory usage of our main program, simply 'make test'.
BENCHMARKS:
	Our benchmarks are located in the 'bench' directory. We benchmarked by running the 'bench.test' program with varying parameters for the size of the tree,
	balance of the tree, and the number of nearest neighbor searches to perform. We have benchmarked the performance of nearest neighbor searches using
	balanced and unbalanced kd-trees as well as differing size trees.


	Results:
	#todo add benchmarking results.






NODE.JS APP:
	Note: You must have the node.js runtime environment set up on your machine prior to running this code. Running 'node app.js' launches the node application,
	which does the following: retrieves a listing of events from the Ticket Evolution API using the Event.listEvents function. When it has received this listing,
	it creates an instance of the 'AlgorithmController' and launches the nearest neighbor program using a member function. Once that has completed, it performs a
	nearest neighbor search using a specific event retrieved from the API as the 'target' event. Finally, it prints data regarding both the target event as well as the
	nearest neighbor that was found.








Balancing

100: 0.002705 seconds	0.734375 Mbytes
1000: 0.003681 seconds	0.867188 Mbytes
10000: 0.015682 seconds	2.468750 Mbytes
100000: 0.170147 seconds	17.582031 Mbytes
1000000: 1.974758 seconds	163.476562 Mbytes
10000000: 23.285349 seconds	1461.988281 Mbytes

NN w/ balance

100: 0.001999 seconds	0.703125 Mbytes
1000: 0.003240 seconds	0.843750 Mbytes
10000: 0.015527 seconds	2.468750 Mbytes
100000: 0.151865 seconds	17.589844 Mbytes
1000000: 1.831353 seconds	163.492188 Mbytes

0.0206566
0.166991
1.58356
