#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<stdlib.h>			//atoi

using namespace std;

int main()
{
    fstream infile("infile.txt",ios_base::in);
    string firstLine;
    getline(infile,firstLine);
    infile.close();
    const char* p = strtok(&firstLine[0]," ");
    while(p) {
        cout<<atoi(p)<<endl;
        p = strtok(NULL," ");
    }
    return 0;
}
