#include "node.h"
#include <bits/stdc++.h> 
using namespace std;

class Huffman{
private:
	node * root;
	map<char, string> codes;
	string source;
	string destination;
public:
	Huffman(string _source, string _destination){
		this->source = _source;
		this->destination = _destination;
		cout<<this->destination<<endl<<_destination;

		map<char, int> frequency;
		char letter;
		freopen(source.c_str(), "r", stdin);
		while(scanf("%c", &letter) != EOF)
			frequency[letter] += 1;
		fclose(stdin);

		this->root = generate_tree(frequency);
		generate_codes(this->root, "");
		writeFile(this->codes);
	}
	node * generate_tree(map<char, int>&);
	void generate_codes(node * , string);
	void writeFile(map<char, string>&);
};

int binaryToDecimal(string bin) {
	while ((int)bin.size() < 8) bin += "0";
	int dec = 0;
	reverse(bin.begin(), bin.end());
	for (int i = 0; i < (int)bin.size(); ++i)
		dec += (bin[i] == '1') * (1 << i);
	return dec;
}

void Huffman::generate_codes(node * root, string currCode){ 
    if (root->getLeft() == NULL && root->getRight() == NULL){
        this->codes[root->getLetter()] = currCode;
        return;
    }
  
    generate_codes(root->getLeft(), currCode + "0"); 
    generate_codes(root->getRight(), currCode + "1");
    return;
}


node * Huffman::generate_tree(map<char, int> &frequency){
	priority_queue<node*, vector<node*>, decltype(&compare)> min_heap(&compare);

	for (map<char,int>::iterator it=frequency.begin(); it!=frequency.end(); ++it)
		min_heap.push(new node(it->first, it->second));

	while(min_heap.size() != 1){
		node *left = min_heap.top();
		min_heap.pop();

		node *right = min_heap.top();
		min_heap.pop();

		node * parent = new node();
		parent -> combine(left, right);
		min_heap.push(parent);
	}
	return min_heap.top();
}

void Huffman::writeFile(map<char, string> &codes){
	string result = "";
	char letter;
	freopen(source.c_str(), "r", stdin);
	while(scanf("%c", &letter) != EOF)
		result += codes[letter];
	fclose(stdin);
	string tmp = result;
	result = "";

	for (int i = 0; i < (int)tmp.size(); i += 8) {
		result += char(binaryToDecimal(tmp.substr(i, 8)));
	}

	size_t size = result.size();
	cout<<destination;
	fstream outFile;
	outFile.open(destination.c_str(), ios::out | ios::binary);
	outFile.write(result.c_str(), size);
	outFile.close();
}