/**
 * 借助strtok实现split
 */
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include<iostream>
#include<string>
using namespace std;
void splitWords()
{
    string line, word, alpha(53,'-');
    string::size_type pos=0, posEnd=0;
    for(int i=0; i<26; ++i) {
        alpha[i] = 'A' + i;
        alpha[i+26] = 'a' + i;
    }
    while(getline(cin,line)) {
		pos = 0;
        while(pos!=string::npos) {
            pos = line.find_first_of(alpha,pos);
            posEnd = line.find_first_not_of(alpha,pos);
			if(pos==posEnd)
				break;
			word = line.substr(pos,posEnd-pos);
			if(word!="-")
				cout<<word<<endl;
            pos = posEnd;
        }
    }
}

int main(int argc,char *argv[])
{
	/*
    if(argc>1)
        freopen(argv[1],"r",stdin);
    else
        freopen("artical.txt","r",stdin);
    freopen("words.txt","w",stdout);
    char s[1024] = " this is  a test,simple * test2!  ";
    const char *d = " ,.!?$:;()[]{}~#&%^…_@|<>'\"\\\t*+=/，。！？：；‘`·《》【】　 ";
    while(gets(s)) {
        char *p = strtok(s,d);
        while(p) {
            printf("%s\n",p);
            p=strtok(NULL,d);
        }
    }
	*/
    //C++形式
    splitWords();
    return 0;
}
