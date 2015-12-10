#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class Vec{
public :
	static void addVector(vector<T> &out,const vector<T> &v1){
		int i,j, s1 = out.size(), s2 = v1.size();
		for(i=0; i<s1 && i<s2; ++i)
			out[i] += v1[i];
		cout<<"***"<<endl;print(out);
	}
	template<typename...Args>
	static void addVector(vector<T> &out,const vector<T> &v1,const Args...args){
		addVector(out,v1);
		addVector(out,args...);
	}
	static void print(vector<T> &vec,const char* str=0){
		if(str) cout<<str<<endl;
		for(int i=0;i<vec.size();++i)
			cout<<vec[i]<<" ";
		cout<<endl;
	}
};
int main()
{
	vector<int> a(4,0), b(4,1), c(4,3);
	Vec<int> vv;
	vv.addVector(a,b,c,a,c);
	vv.print(a,"a");
	vv.print(b,"b");
	return 0;
}
