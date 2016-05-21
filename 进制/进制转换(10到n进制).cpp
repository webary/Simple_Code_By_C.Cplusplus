#include <iostream>
#include <string>
#include <bitset>
using namespace std;

//���Խ�ʮ���Ƶ�decimalת��Ϊbase���Ƶ������浽result
string& transform(unsigned decimal,unsigned base,string &result)
{
	if(base==0)
		return result;
    char str[65] = "0"; //��ֹ����ecimalΪ0���ؿմ�
    int n;
    for(n=0;decimal;++n) {
        int ch = decimal % base;
        if(ch >= 10)
            str[n] = ch - 10 + 'A';
        else
            str[n] = ch + '0';
        decimal /= base;
    }
    for(int i = 0; i < n / 2; i++) {
        char t = str[i];
        str[i] = str[n - 1- i];
        str[n - 1 - i] = t;
    }
    result = str;
    return result;
}
//ͨ��λ����ת��Ϊ2����(֧�ֶԸ�����ת��)
char* getBinaryStr(unsigned num,char dst[])
{
    if(dst==0) //�������봦��
        return 0;
    int i=-1, j=i;
    while((num & (0x80000000>>++i))==0 && i<31);//ֻ���ǰ31λ,Ӧ��num==0
    for(j=i; i<32; ++i)
        dst[i-j] = 48 + ((num & (0x80000000>>i))!=0);
    dst[i-j] = '\0';
    return dst;
}
//����STL������ö�����
string& to_binary(unsigned decimal,string &result)
{
    bitset<64> bs(decimal);
    result = bs.to_string().substr(bs.to_string().find('1'));
    return result;
}
int main()
{
    unsigned decimal;
    string result(33,'\0');
    cout<<"����һ��Ҫת����ʵ��:";
    while(cin>>decimal) {
        cout<<"ת����:"<<endl;
        cout<<"2 ����:\n"<<transform(decimal,2,result)<<endl;
        cout<<to_binary(decimal,result)<<endl;
        cout<<getBinaryStr(decimal,&result[0])<<endl;
        cout<<"8 ����:\n0"<<transform(decimal,8,result)<<endl;
        cout<<"16����:\n0x"<<transform(decimal,16,result)<<endl;
        cout<<"\n����һ��Ҫת����ʵ��:";
    }
    return 0;
}
