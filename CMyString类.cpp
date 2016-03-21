#include <iostream>
#include <cstring>
using namespace std;

class CMyString {
public:
    CMyString(const char* pData = "");
    CMyString(const CMyString& str);
    CMyString& operator=(const CMyString& str);
    ~CMyString();
private:
    char* m_pData;
};

CMyString::CMyString(const char* pData)
{
    cout << "constructor called" << endl;
    if (pData == NULL) { //特殊输入判断
        m_pData = new char[1]; //申请一个字符的空间
        m_pData[0] = '\0';
    } else { //参数有效则从字符串获得大小和内容
        m_pData = new char[strlen(pData) + 1];
        strcpy(m_pData, pData);
    }
}
CMyString::CMyString(const CMyString& str)
{
    cout << "copy constructor called" << endl;
    m_pData = new char[strlen(str.m_pData) + 1];
}
CMyString::~CMyString()
{
    cout << "destructor called" << endl;
    delete m_pData;
}
CMyString& CMyString::operator=(const CMyString& other)
{
    cout << "operator= called" << endl;
    if(this == &other)
        return *this;
    delete[] m_pData;
    m_pData = NULL;
    m_pData = new char[strlen(other.m_pData) + 1];
    strcpy(m_pData, other.m_pData);
    return *this;
}

int main()
{
    CMyString str1("hello"), str2(str1), str3, str4;
    cout << __LINE__ << endl;
    str3 = str1 = "hello";
    str4.operator = ("lym");
    cout << __LINE__ << endl;
    str4 = "world";
    cout << __LINE__ << endl;
}
