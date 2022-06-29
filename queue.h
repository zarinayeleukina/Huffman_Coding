#include <iostream>
#include <string>

using namespace std;

struct Node {
        char symbol;
        int frequency;
        Node * left;
        Node * right;
	string code;
};

struct Queue_Node {
	Node *qn;
	Queue_Node *next;
	int level;
};

class Queue {
	Queue_Node * head;
	Queue_Node * tail;
public:
	Queue();
	~Queue();
	void Push(Node *x, int l);
	Node* Pop(int * l);
	bool Is_Empty() const;
};
