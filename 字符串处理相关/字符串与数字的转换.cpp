#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
using namespace std;
//��תarr��ǰlen���ַ�
void reverse(char *str,int len=0)
{
    if(len<=0)
        len = strlen(str);
    char temp;
    for(int i= 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = temp;
    }
}
void num2string(int n,char*s)
{
    memset(s,0,10);
    int len=0;
    do {
        s[len++] = n%10 + 48;
        n/=10;
    } while(n>0);
    reverse(s,len);
}
int string2num(const char* s)
{
    int len = 0,n = s[len++] - '0';
    while(s[len]>='0' && s[len]<'9')
        n = n * 10 + s[len++] - '0';
    return n;
}
int main()
{
    int num;
    char p[11];
    cout<<"please input a number: ";
    cin>>num;

    cout<<"���ֵ��ַ�����";
    num2string(num,p);
    cout<<p<<endl;

    //�����ַ�����ת��
    ostringstream ss;
    ss<<num;
    cout<<ss.str()<<endl;

    cout<<"�ַ��������֣�";
    num = string2num(p);
    cout<<num<<endl;

    return 0;
}

/*
#include <stdio.h>
//#include <string.h>
#include <stdlib.h>			//atoi
int main() {
    int n=12345;
    char s[20],ss[20];

    sprintf(s,"%d",n);

	char *itoa(int num,char *str,int radix);
    itoa(n,ss,10);
    n=atoi(ss);
    printf("itoa & atoi ת�������\nss=\"%s\"\nn= %d\n\n",ss,n);

    printf("s=\"%s\"\n",s);
    printf("n= %d\n",n);
    return 0;
}
char *itoa(int num,char *str,int radix) {
    char index[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";    // ������
    unsigned unum;
    int i=0,j,k;
    if(radix==10&&num<0) { // ʮ���Ƹ���
        unum=(unsigned)-num;
        str[i++]='-';
    }else // �������
		unum=(unsigned)num;
    do {    // ����
        str[i++]=index[unum%(unsigned)radix];
        unum/=radix;
    } while(unum);
    str[i]='\0';     // ת��
    if(str[0]=='-') k=1; // ʮ���Ƹ���
    else k=0;
    char temp;
    for(j=k; j<=(i-1)/2; j++){
        temp=str[j];
        str[j] = str[i-1+k-j];
        str[i-1+k-j] = temp;
    }
    return str;
}
*/

