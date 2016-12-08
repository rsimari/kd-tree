README.md

Presentation Deck: https://docs.google.com/presentation/d/169yjtvhggSNyJT2a8LMQeVJNUUQzUxAIwzljduL_NlE/edit?usp=sharing

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


2D Tree Balancing Times

| Nodes    | Execution Time (s) | Memory (MBytes) |
|----------|--------------------|-----------------|
| 100      | .002705            | 0.734375        |
| 1000     | .003681            | 0.867188        |
| 10000    | .015682            | 2.468750        |
| 100000   | .170147            | 17.582          |
| 1000000  | 1.974              | 163.47          |
| 10000000 | 23.285             | 1461.989        |

Nearest neighbor on balanced tree (1000 searches)

| Nodes    | Execution Time (s) |
|----------|--------------------|
| 100      | .00899             |
| 1000     | .01659             |
| 10000    | .0213              |
| 100000   | .02599             |
| 1000000  | .0340              |
| 10000000 | .0653              |

Nearest neighbor on unbalanced tree (1000 searches)

| Nodes    | Execution Time (s) |
|----------|--------------------|
| 100      | .0206566           |
| 1000     | .166991            |
| 10000    | 1.58356            |
| 100000   | 8.4532             |
| 1000000  | INF                |
| 10000000 | INF                |



	NODE.JS APP:
		Note: You must have the node.js runtime environment set up on your machine prior to running this code. Running 'node app.js' launches the node application,
		which does the following: retrieves a listing of events from the Ticket Evolution API using the Event.listEvents function. When it has received this listing,
		it creates an instance of the 'AlgorithmController' and launches the nearest neighbor program using a member function. Once that has completed, it performs a
		nearest neighbor search using a specific event retrieved from the API as the 'target' event. Finally, it prints data regarding both the target event as well as the
		nearest neighbor that was found.
