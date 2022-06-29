#include <iostream>
#include "queue.h"

class Priority_Queue_Min {
private:
	Node ** heap;
	int heap_size;
	int max_size;
	void Sift_Up(int index);
	void Sift_Down(int index);
public:
	Priority_Queue_Min (int n, char * symbols, int * frequencies);
	Node * Extract_Min();
	Node * Build_Huffman_Tree();
	void Insert(Node * new_elem);
	void print_node(Node *x);
	void printCodes(Node *x);
	~Priority_Queue_Min();
	bool IsEmpty();
	bool IsFull();
	int encode(string s, int n);
	void decode(int n);

};
