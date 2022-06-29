#include "queue.h"
#include <string>
using namespace std;

	Queue::Queue() {
		head = tail = NULL;
	}
	Queue::~Queue() {
		Queue_Node * tmp = head;
		while(tmp != NULL) {
			tmp = tmp -> next;
			delete head;
			head = tmp;
		}
	}

	void Queue::Push(Node * x, int l) {
		Queue_Node * tmp = new Queue_Node;
		tmp -> qn = x;
		tmp -> next = NULL;
		tmp -> level = l;
		if(head == tail && head == NULL){
			head = tail = tmp;
		}
		else if(head == tail)
			head -> next = tail = tmp;
		else {
			tail = tail -> next = tmp;
		}
	}
	Node * Queue::Pop(int * l){
		Node * rez = head -> qn;
		*l = head -> level;
		if (head == tail){
			delete head;
			head = tail = NULL;
		}
		else {
			Queue_Node * tmp = head -> next;
			delete head;
			head = tmp;
		}
		return rez;
	}

	bool Queue::Is_Empty() const{
		if(head == tail && head == NULL)
			return true;
		return false;
	}
