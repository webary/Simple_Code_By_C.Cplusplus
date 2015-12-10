#include<iostream>
#include<cassert>
using namespace std;
#define PRINT(x) cout<<#x<<" = "<<x

class MyString{
	unsigned len;
	char *s;
public:
	MyString(){
		s = 0;
		len = 0;
	}
	MyString(const char *p){
		int i=-1;
		while(p[++i]);				//判断数组长度
		len=i;
		s=new char[len+1];
		i=0;
		while(s[i]=p[i++]);			//将每个元素复制
	}
	MyString(const MyString& str){
		s=new char[str.len+1];
		int i=0;
		while(s[i]=str.s[i++]);
		s[i]=0;
		len=str.len;
	}
	~MyString(){
		delete[] s;
//		cout<<"~MyString() called"<<endl;
	}
	unsigned length()const{
		return len;
	}
	const char* c_str()const{
		return s;
	}
	MyString operator + (const MyString& s2) const{
		MyString s3;
		s3.len = len + s2.len;
		s3.s = new char[s3.len+1];
		unsigned i=0;
		while(s3.s[i]=s[i])
			++i;
		while(s3.s[i]=s2.s[i-len])
			++i;
		s3.s[i] = 0;
		return s3;
	}
	MyString& operator=(const MyString& s2){
		if(this==&s2)			//自赋值检测
			return *this;
		if(s!=NULL)
			delete[] s;
		len=s2.len;
		s=new char[len+1];
		int i=0;
		while(s[i]=s2.s[i++]);
		return *this;
	}
	MyString& operator+=(const MyString& s2){			//有问题
		MyString s3(*this);    //s3先保存*this
		delete[] s;
		len = s2.len + s3.len;
		s = new char[len+1];
		unsigned i=0;
		while(s[i]=s3.s[i])
			++i;
		while(s[i]=s2.s[i-s3.len])
			++i;
		s[i] = 0;
		return *this;
	}
	char& operator[](unsigned i){
		assert(i<len);
		return this->s[i];
	}
	const char& operator[](unsigned i)const{
		assert(i<len);
		return this->s[i];
	}
	friend ostream& operator<<(ostream &out,const MyString& str){
		out<<str.s;
		return out;
	}
	 bool operator==(const MyString& str2){
		unsigned i=0;
		while(s[i]!=NULL && s[i]==str2.s[i])
			++i;
		return s[i]==NULL && str2.s[i]==NULL;
	}
};

int main()
{
	MyString str1("China");
	MyString str[3];
	str[0]=str1;
	PRINT(str[0])<<endl;
	PRINT(str1)<<endl;
	str1 += str[0];
	PRINT(str1)<<endl;
	str[1]=str[0]+str1;
	PRINT(str[1])<<endl;

	cout<<str1.c_str()<<"  "<<str1.length()<<endl;
	cout<<"str1:"<<str1<<endl;
	cout<<"str[1]:"<<str[1]<<endl;
	cout<<(str1==str[2])<<endl;
	return 0;
}

