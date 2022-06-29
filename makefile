all: prog

prog: main.o priority_queue_min.o queue.o
	g++ main.o priority_queue_min.o queue.o -o prog

main.o: main.cpp
	g++ -c main.cpp

priority_queue_min.o: priority_queue_min.cpp
	g++ -c priority_queue_min.cpp

queue.o: queue.cpp
	g++ -c queue.cpp

clean:
	rm *.o prog
