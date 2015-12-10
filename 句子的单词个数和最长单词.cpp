#include<iostream>
#include<string>
#include <ctype.h>
using namespace std;

int numOfWord(string &s){
	bool flag=false;
	unsigned len=s.length(), num=0;
	for(int i=0;i<len;i++){
	//	if(s[i]>='a' && s[i]<='z' || s[i]>='A' && s[i]<='Z'){
		if(isalpha(s[i])){
			if(flag==false){
				flag=true;  num++;
			}
		}
		else	flag=false;
	}
	return num;
}
int longestWord(string &s,int &maxNum){
	bool flag=false; maxNum=0;
	int len=s.length(), max_i=0, templong, temp_i;
	for(int i=0;i<=len;i++){			//注意要写作i<=len，若为i<len会略过最后一个单词
		if(isalpha(s[i])){
			if(!flag){
				flag=true;  templong=1;  temp_i=i;
			}
			else	templong++;
		}
		else if(flag){
			flag=false;//cout<<templong<<' ';
			if(templong > maxNum){
				maxNum=templong;
				max_i=temp_i;
			}
		}
	}
	return max_i;
}
int main()
{
	string s;
	cout<<"please input a string :";
	getline(cin,s);
	int num=numOfWord(s),maxNum;
	cout<<"\nstring \""<<s<<"\" has "<<num<<" words"<<endl;
	int max_i=longestWord(s,maxNum);
	cout<<"The longest word is ：";
	char * p=&s[max_i];
	for(int i=0;i<maxNum;p++,i++)
		cout<<*p;
	cout<<endl;
	return 0;
}
