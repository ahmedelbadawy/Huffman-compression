#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>
#include <bits/stdc++.h>

using namespace std;

struct image
{
    int width = 0, hight = 0, maxwhite = 255;
    vector<int> Pixels;
};
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


static void getCodes(struct Node *root, string str, map<int, string> &valueTOcode)
{
    if (!root)
        return;

    if (root->data != 256)
    {

        valueTOcode[root->data]=str;

    }
    if(root->left!=NULL)
    getCodes(root->left, str + "0", valueTOcode);
    if(root->right!=NULL)
    getCodes(root->right, str + "1",valueTOcode);
}

inline void buildhuffmantree(vector<int>freq, map<int, string> &valueTOcode)
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

    getCodes(ex.top(), "", valueTOcode);
}


inline void fileinfo(image &data, string file_path)
{

    ifstream imagefile;
    imagefile.open(file_path, ios::binary);
    char pixel;
    string line = "11"; //to store the input line from header
    getline(imagefile, line);
    //cout << "pgm type :" << line << endl; //first line of output
    getline(imagefile, line);
    stringstream cast;
    cast << line;
    string width;
    string hight;
    cast >> width;
    cast >> hight;
    //cout<<width<<"  "<<hight;
    data.width = stoi(width);
    data.hight = stoi(hight);
    //cout << data.width << " " << data.hight << endl; //second line of output
    getline(imagefile, line);
    cast << line;
    cast >> data.maxwhite;
    //cout << "max white is " << data.maxwhite << endl; //third output line
    //cout << data.width * data.hight << endl;

    int i = 0;
    while (imagefile.eof() == 0)
    {
        imagefile.get(pixel);
        unsigned char C = (unsigned char)(pixel);
        data.Pixels.push_back((int)(C));
        // cout<<data.Pixels[i]<<" ";
        i++;
    }
}

inline void writeOnpgm(string filename, image data)
{
    ofstream write(filename);
    write << "P5" << endl;
    write << data.width << " " << data.hight << endl;
    write << data.maxwhite << endl;
    vector<char> wr;
    int J = 0;
    while (J < data.width * data.hight)
    {
        wr.push_back((char)data.Pixels[J]);
        J++;
    }

    for (int i = 0; i <= data.width * data.hight; i++)
        write.put(wr[i]);
}

inline string serialize(image data, map<int, string> valueTOcode)
{
    string encodedData = "";
    for (int i = 0; i < data.Pixels.size(); i++)
    {
        encodedData += valueTOcode[data.Pixels[i]];
    }
    int paddingBits_Num = 8 - (encodedData.size() % 8);
    for (int i = 0; i < paddingBits_Num; i++) //make sure the string is divisible by 8
        encodedData += "0";
    string binary_padding = bitset<8>(paddingBits_Num).to_string(); //convert the number of badding bits to a binary number using bitsit
                                                                    //  cout << paddingBits_Num << " " << binary_padding.size() << " " << binary_padding << endl;

    encodedData.insert(0, binary_padding);
    return encodedData;
}
inline void writeEncoded(string serializedData)
{
    string split_8 = "";
    int dec;

    int numSplits = serializedData.size() / 8;
    ofstream compressedFile("compressMod.enc");
    for (int i = 0; i < numSplits; i++)
    {
        split_8 = serializedData.substr(i * 8, 8);
        dec = stoi(split_8, 0, 2);
        char decToch = (char)dec;
        compressedFile << decToch;
    }
}

inline void writeCodes( image data, map<int, string> valueTOcode)
{
    ofstream codesFile("codeFile.freq");
    codesFile << data.width << " " << data.hight << endl;
    for (auto &[key, value] : valueTOcode)
    {
        codesFile<<key<<" "<<value<<endl;
    }
}

inline double SizeOfFile(string fileName)
{
    ifstream SizeOfFile(fileName, ios::binary);
    SizeOfFile.seekg(0, ios::end);
    double finalSize = SizeOfFile.tellg();
    return finalSize;
}
