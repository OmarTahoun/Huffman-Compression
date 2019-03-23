#include <bits/stdc++.h> 
using namespace std;

class node{
private:
	char letter;
	int frequency;
	node * left, * right;
	
public:
	node(){};
	node(char letter, long long frequency){
		left = right = NULL;
		this->letter = letter;
		this->frequency = frequency;
	};

	inline char getLetter(){ return this->letter;}
	inline int getFrequency(){ return this->frequency;}
	inline node * getLeft(){ return this->left;}
	inline node * getRight(){ return this->right;}

	void combine(node * left, node * right){
		this->left = left;
		this->right = right;
		this->frequency = left->frequency + right->frequency;
	}
};

bool compare(node* &left, node* &right){
	if(left->getFrequency() > right->getFrequency())
		return true;
	return false;
}
