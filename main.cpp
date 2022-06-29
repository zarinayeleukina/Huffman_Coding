#include <iostream>
#include <fstream>
#include <string>
#include "priority_queue_min.h"

using namespace std;

string del_same(string s, int i) { //delete the same symbols
	string str;
	for(int j=i+1; j<s.size(); j++) {
		if(s[i]!=s[j])
			str += s[j];
	}
	return str;
}

int elem_num(string s) {  //diff elem numb
	int cnt = 0;
	string g = s;
	while(g.length() != 0) {
		g = del_same(g,0);
		cnt++;
	}
	return cnt;
}

int calcFreq(string s) {  //freq of 1st elem
	int cnt = 1;
	for(int i = 1; i < s.length(); i++) {
		if(s[0] == s[i])
			cnt++;
	}
	return cnt;
}

void storeCodes(int n, string s, char *c, int *f) {  //save char, int in array
	string g = s;
	for(int i=0; i<n; i++) {
		c[i] = g[0];
		f[i] = calcFreq(g);
		g = del_same(g,0);
	}
}

int main(int argc, char *argv[]){
	ifstream input(argv[1]);
	if(argc != 2){
		cout << "ERROR" << endl;
		return 0;
	}
	string str;
	while(input){
		string tmp;
		getline(input, tmp);
		if(!input.eof())
			tmp += '\n';
		str += tmp;
	}
	input.close();

	int n = elem_num(str);  //text size
	char *c = new char[n];
	int *f = new int[n];
	storeCodes(n, str, c, f);

	Priority_Queue_Min tree(n, c, f);
	Node * res = new Node[1];
	res = tree.Build_Huffman_Tree();
	tree.printCodes(res);
	int numb = tree.encode(str, n);
	tree.decode(numb);
	return 0;
}
