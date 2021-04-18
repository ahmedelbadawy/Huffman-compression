#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<bitset>

using namespace std;

inline void readCompressed(string &str)
{
    ifstream compressedFile;
    compressedFile.open("compressMod.enc");
    char ch;
    while(compressedFile>> noskipws >>ch)
    {
        unsigned char unCh= ch;
        int x= (int)unCh ;
        str +=bitset<8>(x).to_string() ;

    }

    string s= str.substr(0,8);
  int dec = stoi(s,0,2);
  str.erase (0,8) ;
  for (int i=0 ; i<dec ;++i)
  str.pop_back();

  }


inline void readCodes(vector<int> &value,vector<string> &codearr, int &width, int &hight){
    ifstream codesFile("codeFile.freq");
    string value_casting="";int i=0; string codeCasting="";
    codesFile>>width>>hight;
    while(codesFile>>value_casting>>codeCasting){

     codearr.push_back(codeCasting);
    value.push_back(stoi(value_casting));

    }
for(int i=0;i<codearr.size();i++){
}
}

inline void decode_write( map<string,int> codeTOvalue, string binary_string,int width,int hight)
{
    ofstream pgm_write("P5.pgm");
    pgm_write<<"P5"<<endl;
    pgm_write<<width<<" "<<hight<<endl;
    pgm_write<<"255"<<endl;
    string is_code= "" ;
    vector<char> wr;
    int x ;
    for(int i=0; i < binary_string.size(); ++i)
    {

       is_code += binary_string.substr(i,1);

       if(codeTOvalue.count(is_code)>0)
       {
        x = codeTOvalue[is_code];
        unsigned char ch = (unsigned char) x ;
        pgm_write<<ch ;
        is_code="";
       }
    }

}
#endif // DECOMPRESSION_H
