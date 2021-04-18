#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <bitset>
using namespace std;

struct image
{
    int width = 0, hight = 0, maxwhite = 255;
    vector<int> Pixels;
};

void fileinfo(image &data, string filename)
{

    ifstream imagefile;
    imagefile.open(filename, ios::binary);
    char pixel;
    string line = "11"; //to store the input line from header
    getline(imagefile, line);
    cout << "pgm type :" << line << endl; //first line of output
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
    cout << data.width << " " << data.hight << endl; //second line of output
    getline(imagefile, line);
    cast << line;
    cast >> data.maxwhite;
    cout << "max white is " << data.maxwhite << endl; //third output line
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


string serialize(image data, map<int, string> valueTOcode)
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
void writeEncoded(string serializedData)
{
    string split_8 = "";
    int dec;
cout<<"please enter the name for compressed file without extension"<<endl;
string encName=""; cin>>encName; encName+=".enc";
    int numSplits = serializedData.size() / 8;
    ofstream compressedFile(encName);
    for (int i = 0; i < numSplits; i++)
    {
        split_8 = serializedData.substr(i * 8, 8);
        dec = stoi(split_8, 0, 2);
        char decToch = (char)dec;
        compressedFile << decToch;
    }
}

void writeCodes(map<int, string> valueTOcode, image data)
{cout<<"please enter the codesFile Name without extension"<<endl;
string codefileName=""; cin>>codefileName; codefileName+=".freq";
 
    ofstream codesFile(codefileName);
    codesFile << data.width << " " << data.hight << endl;
    for (auto &[key, value] : valueTOcode)
    {
        codesFile<<key<<" "<<value<<endl;
    }
}