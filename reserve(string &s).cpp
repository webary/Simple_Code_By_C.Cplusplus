#include <iostream>
#include <string>

using namespace std;

void reverse(string & s,bool flag=true)
{
	static int i=0;
	if(flag)  i=0;
	int len=s.length();
	if(i<len/2){
		s[i]^=s[len-i-1];
		s[len-i-1]^=s[i];
		s[i]^=s[len-i-1];
		i++;
		reverse(s,false);
	}
}

int main(){
	string s1;
	cout<<"enter a string : ";
	getline(cin,s1);
	reverse(s1);
	cout<<s1<<endl;
	string s2;
	cout<<"enter a string : ";
	getline(cin,s2);
	reverse(s2);
	cout<<s2<<endl;

	return 0;
}
