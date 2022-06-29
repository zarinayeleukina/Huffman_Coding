#include "priority_queue_min.h"
#include <fstream>

using namespace std;

void swap(Node **x, Node **y) {
        Node *tmp = *x;
        *x = *y;
        *y = tmp;
}


    void Priority_Queue_Min::Sift_Up(int index){
        while (index > 1){
    		if (heap[index]->frequency < heap[index/2]->frequency) {
    			swap(heap[index], heap[index/2]);
    			index /= 2;
    		}
    		else break;
	    }
    }
    void Priority_Queue_Min::Sift_Down(int index){
        while(index < heap_size){
        	if(2*index > heap_size) //нет потомков
        		return;
        	if(2*index == heap_size){ //один потомок
        		if(heap[index]->frequency > heap[2 * index]->frequency){
        		    swap(heap[index], heap[2 * index]);
        			index *= 2;
        		}
        		else
        			return;
        	}
        	else{ //два потомка
        		int minim = min(heap[2*index]->frequency, heap[2*index+1]->frequency);
        		if(heap[index]->frequency <= minim)
        			return;
        		else{
        			if(heap[2*index]->frequency == minim){
        			    swap(heap[index], heap[2*index]);
        				index *= 2;
        			}
        			else{
        			    swap(heap[index], heap[2*index + 1]);
        				index = index*2 + 1;
        			}
        		}
        	}
        }
    }


Priority_Queue_Min::Priority_Queue_Min(int n, char *symbols, int *frequencies) {
	heap_size = n;
	max_size = n+1;
	heap = new Node* [n+1];
	for(int i=1; i<n+1; i++) {
		heap[i] = new Node;
		heap[i]->symbol = symbols[i-1];
		heap[i]->frequency = frequencies[i-1];
		heap[i]->left = NULL;
		heap[i]->right = NULL;
	}
	for(int j=n; j>0; j--)
		Sift_Down(j);
}

bool Priority_Queue_Min::IsEmpty(){
	return heap_size == 0;
}
    Node * Priority_Queue_Min::Extract_Min(){
        if (IsEmpty()){
            cout << "Heap is empty" << endl;
            return NULL;
        }
        else{
            Node * tmp = heap[1];
            heap[1] = heap[heap_size];
            heap_size--;
            if(heap_size > 0)
                Sift_Down(1);
            return(tmp);
        }
    }

void Priority_Queue_Min::Insert(Node * new_elem){
        if(!IsFull()){
            if(heap_size == 0)
                heap[1] = new_elem;
            else{
                heap[heap_size + 1] = new_elem;
                Sift_Up(heap_size + 1);
            }
            heap_size++;
        }else
            cout << "Not enough space in array" << endl;
}

bool Priority_Queue_Min::IsFull(){
	return heap_size == max_size;
}

Node * Priority_Queue_Min::Build_Huffman_Tree(){
        while(heap_size != 1){  //Nodes of lowest frequencies
            Node * left = Extract_Min();
            Node * right = Extract_Min();
            int sum = left->frequency + right->frequency;
            Node * tmp = new Node;
            tmp->frequency = sum;
            //tmp->symbol = '+'; //random symbol
            tmp->left = left;
            tmp->right = right;
            Insert(tmp);
        }
        Node * root = heap[1];
        return root;
}

void Priority_Queue_Min::print_node(Node *x) {
		cout << x->symbol << " " <<  x->frequency << " " <<  x->code << endl;
}

void Priority_Queue_Min::printCodes(Node * x){ // traverse the huffman tree and store codes
 	Queue q;
	q.Push(x, 1);
	int previous_level = 1;
	int current_level;
	string s1 = "0";
	string s2 = "1";
	while(!q.Is_Empty()) {
		Node * tmp = q.Pop(&current_level);
		if(tmp!=NULL) {
			if(tmp->left != NULL) {
				tmp->left->code += tmp->code;
				tmp->left->code.append(s1);
			}
			if(tmp->right != NULL) {
				tmp->right->code += tmp->code;
				tmp->right->code.append(s2);
			}
			/*if(tmp->left == NULL && tmp -> right == NULL) //Print huffman codes
				print_node(tmp);*/
			q.Push(tmp->left, current_level + 1);
			q.Push(tmp->right, current_level + 1);
		}
		previous_level = current_level;
	}
}

int Priority_Queue_Min::encode(string s, int n) {
	Node ** bin;
	bin = new Node * [n+1];
	Queue q;
	q.Push(heap[1], 1);
	int previous_level = 1;
	int current_level;
	int i = 1;
	while(!q.Is_Empty()) {
		Node * tmp = q.Pop(&current_level);
		if(tmp != NULL){
			if(tmp->left == NULL && tmp->right == NULL) {
				bin[i] = new Node;
				bin[i] = tmp;
				i++;
			}
			q.Push(tmp -> left, current_level + 1);
			q.Push(tmp -> right, current_level + 1);
		}
		previous_level = current_level;
	}

	string codes;	//make binary code from txt
	for(int i = 0; i < s.length(); i++)
		for(int j = 1; j < n + 1; j++)
			if(s[i] == bin[j] -> symbol)
				codes += bin[j] -> code;

	//fill the rest ones with 0s
	int zeroes = 8 - (codes.length() % 8); //1 char = 8 bits
	for(int i = 0; i < zeroes; i++)
		codes += '0';

	//save to txt file
	ofstream output("encoded.txt");

	while(codes.length() / 8 != 0){
		int *mas = new int[8];
		for(int i = 0; i < 8; i++)
			if(codes[i] == '0')
				mas[i] = 0;
			else
				mas[i] = 1;
		codes.erase(0,8);
		char ch1 = '('; //0010 1000
		char ch0 = ')'; //0010 1001
		ch1 = ch1 ^ ch0;
		char ch2 = ':'; //0011 1010
		ch0 = ch1 & ch2; // ch1 = 0000 0001   ch0 = 0000 0000
		for(int i = 7; i >= 0; i--){
			if(mas[i] == 1)
				ch0 = ch0 ^ ch1;
			ch1 = ch1 << 1;
		}
		output << ch0;
	}
	output.close();
	return zeroes;
}
void Priority_Queue_Min::decode(int numb) {
	ifstream input("encoded.txt");
	string bintxt;
	while(input){
		string line;
		getline(input, line);
		if(!input.eof())
			line += '\n';
		bintxt += line;
	}
	input.close();

	int i = 0;
	string txt;
	while(i < bintxt.length()){
		string subtxt;
		int * bits = new int[8];
		char ch1 = '(';
		char ch2 = ')';
		ch1 = ch1 ^ ch2;  // ch1 = 0000 0001
		for(int j = 7; j >= 0; j--){
			if(bintxt[i] & ch1)
				bits[j] = 1;
		 	else
				bits[j] = 0;
			ch1 = ch1 << 1;
		}
		for(int j = 0; j < 8; j++)
			if(bits[j] == 0)
				subtxt += '0';
			else
				subtxt += '1';
		txt += subtxt;
		i++;
	}
	txt.erase(txt.length() - numb, numb); //remove added additional 0s

	ofstream output("decoded.txt");
	while(txt.length() != 0){
		Node * tmp = heap[1];
		int j = 0;
		string subtxt;
		while(1){
			if(txt[j] == '0' && tmp -> left != NULL)
				tmp = tmp -> left;
			else if(txt[j]=='1' && tmp->right!=NULL)
				tmp = tmp -> right;
			else if(tmp->left==NULL && tmp->right==NULL) {
				subtxt += tmp -> symbol;
				subtxt += tmp -> code;
				break;
			}
			j++;
		}
		output << subtxt[0];
		subtxt.erase(0,1);
		txt.erase(0, subtxt.length());
	}
	output.close();
}
Priority_Queue_Min::~Priority_Queue_Min() {
	for(int i = 1; i <= heap_size; i++)
		delete heap[i];
	delete [] heap;
}
