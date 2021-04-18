#include "read.hpp"
#include <bits/stdc++.h>
#include <map>

using namespace std;

struct Node
{
	int data;
	int freq;
	Node *left, *right;

	Node(int data, int freq)
	{
		this->data = data;
		this->freq = freq;
		left = right = NULL;
	}
};

struct compare
{
	bool operator()(Node *l, Node *r)
	{
		return (l->freq > r->freq);
	}
};


map<int, string> valueTOcode;
void getCodes(struct Node *root, string str)
{
	if (!root)
		return;

	if (root->data != 256)
	{
	
		valueTOcode[root->data]=str;
	
	}
	if(root->left!=NULL)
	getCodes(root->left, str + "0");
	if(root->right!=NULL)
	getCodes(root->right, str + "1");
}

void buildhuffmantree(vector<int>freq)
{
	struct Node *left, *right, *top;

	priority_queue<Node *, vector<Node *>, compare> ex;

	for (int i = 0; i < 256; ++i)
		if (freq[i] > 0)
			ex.push(new Node(i, freq[i]));

	while (ex.size() != 1)
	{

		left = ex.top();
		ex.pop();

		right = ex.top();
		ex.pop();

		top = new Node(256, left->freq + right->freq);

		top->left = left;
		top->right = right;

		ex.push(top);
	}

	getCodes(ex.top(), "");
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		// Tell the user how to run the program if they enter the command incorrectly.
		std::cerr << "Usage: " << argv[0] << " filepath " << std::endl;
		return 1;
	}

	string filepath = argv[1];

	image data;
	std::cout << "Processing image file " << filepath << endl;
	fileinfo(data, filepath);
	cout << endl;
	vector<int>freq(256,0);
	int i = 0;
	while (i < data.Pixels.size())
	{
		++freq[data.Pixels[i]];
		++i;
	}

	std::cout << "Begin process of compressing data" << endl;
	buildhuffmantree(freq);
	string serializedData = serialize(data, valueTOcode); //a string of zeros and ones with the first 8 bits representing the number of padding bits added at the end

	writeEncoded(serializedData);
	writeCodes(valueTOcode, data);
	return 0;
}
