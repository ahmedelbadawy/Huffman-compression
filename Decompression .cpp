#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<bitset>
using namespace std;
struct image{
    int width=0, hight=0, maxwhite=255;
vector<int> Pixels;
};

map<string,int> codeTOvalue;

void readCompressed(string &str)
{
    ifstream compressedFile;
    cout<<"enter the name of the .enc file you wish to decompress"<<endl;
    string decompressFile=""; cin>>decompressFile; decompressFile+=".enc";
    compressedFile.open(decompressFile);
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
  //cout<<str ;
  }


void readCodes(vector<int> &value,vector<string> &codearr, int &width, int &hight){
    cout<<"please enter the name of the associated .freq file"<<endl;
    string decompressFreq=""; cin>>decompressFreq; decompressFreq+=".freq";
    ifstream codesFile(decompressFreq);
    string value_casting="";int i=0; string codeCasting="";
    codesFile>>width>>hight;
    while(codesFile>>value_casting>>codeCasting){
     
     codearr.push_back(codeCasting);
    value.push_back(stoi(value_casting));
    
    }

}

void decode_write( map<string,int> codeTOvalue, string binary_string,int width,int hight)
{
    string name ="" ;
    cout<<"Please enter the name of decomparssed image without extention"<<endl ;
    cin>>name ;
    name += ".pgm" ;
    ofstream pgm_write(name);
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


int main()
{
    string binary_string="";
    readCompressed(binary_string) ;
    vector<int>value;
    vector<string>codearr;
     int width=0; int hight=0;
    readCodes(value,codearr,width,hight);
    
    for(int i=0; i<codearr.size();i++)
    {
	codeTOvalue[codearr[i]]= value[i];
     }
   
     decode_write(codeTOvalue , binary_string,width,hight);
}
