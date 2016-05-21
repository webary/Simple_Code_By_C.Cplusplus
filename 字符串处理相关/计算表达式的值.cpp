//���ʽ��ֵ
#include<iostream>
#include<cstdlib>
using namespace std;
template<class T>
struct Node {
    T data;
    Node<T> *next;
};

template<class T>
class LinkStack {
public:
    LinkStack();
    ~LinkStack();
    bool IsEmpty();
    LinkStack<T>& Push( T x );
    LinkStack<T>& Pop( T &x );
    T GetTop();
    void Process( char* p );//������ʽ
    int Op_val( char ch );   //�������������
    int Calculate( T x,T y,char p );
private:
    Node<T> *top;
};

template<class T>
LinkStack<T>::LinkStack() { //����ͷ�巨����ջ
    top=NULL;
}

template<class T>
LinkStack<T>::~LinkStack() { //�ͷ�ջ
    Node<T> *p,*q;
    p=top;
    while( p ) {
        q=p;
        p=p->next;
        delete q;
    }
}

template<class T>
bool LinkStack<T>::IsEmpty() { //�п�
    return( top==NULL );
}

template<class T>
LinkStack<T>& LinkStack<T>::Push( T x ) { //��ջ
    Node<T> *p;
    p=new Node<T>;
    p->data=x;
    p->next=top;
    top=p;
    return *this;
}

template<class T>
LinkStack<T>& LinkStack<T>::Pop( T &x ) { //��ջ
    if( IsEmpty() ) {
        cout<<"ջ�գ���ֹ��ջ����"<<endl;
        exit(1);
    }
    Node<T> *p;
    p=top;
    x=p->data;
    top=p->next;
    delete p;
    return *this;
}

template<class T>
T LinkStack<T>::GetTop() { //��ȡջ��Ԫ��
    if( IsEmpty() ) {
        cout<<"ջ�գ��޷���ȡջ������"<<endl;
        exit(1);
    }
    return( top->data );
}

template<typename T>
void LinkStack<T>::Process( char* p ) { //������ʽ
    LinkStack<char> op;
    int i = 0,tag;
    T sum = 0;
    op.Push('#');  //�����opջ�Ƚ�#
    do {
        tag = 1;
        if( p[i]>='0'&&p[i]<='9' )   //p[i]Ϊ����ʱ��ջ
            Push( (p[i]-48) );
        else if( op.Op_val(p[i]) > op.Op_val(op.GetTop()) ) { //����������������opջ
            op.Push( p[i] );
            if( p[i]=='(' )
                tag=0;
        } else if( op.GetTop()=='('&& tag ) //opջ��Ϊ�����ţ����������ջ
            op.Push( p[i] );
        else {
            //�����p[i]������С��opջ�����������м���
            while(op.Op_val(p[i])<=op.Op_val(op.GetTop())&&op.GetTop()!='('&&op.GetTop()!='#') {
                T x,y;
                char p;
                Pop( x );
                Pop( y );
                op.Pop( p );
                sum = Calculate(x,y,p); //����Caculate����������ֵ����
                cout<<"������μ���ֵ:";
                cout<<sum<<endl;
                Push( sum );
            }
            if( op.GetTop()=='#'&&p[i]!='#' ) //opջ��ֻʣ#����p[i]!=#ʱp[i]��ջ
                op.Push(p[i]);
            if( p[i]==')' && op.GetTop()=='(' ) { //����ƥ��ʱ'('��ջ
                char p;
                op.Pop( p );
            }
        }
        i++;
    } while( !(p[i-1]=='#'&&op.GetTop()=='#') );  //p[i]��opջ��ͬʱΪ#��ʱѭ����ֹ
    cout<<endl<<"������ʽֵΪ:";
    cout<<sum<<endl;
}

template<typename T>
int LinkStack<T>::Op_val( char ch ) { //���������������
    switch( ch ) {
    case'(':
        return 5;
        break;
    case')':
        return 2;
        break;
    case'*':
        return 4;
        break;
    case'/':
        return 4;
        break;
    case'+':
        return 3;
        break;
    case'-':
        return 3;
        break;
    case'#':
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

template<typename T>
int LinkStack<T>::Calculate( T x, T y, char p ) { //��ֵ���㲢����
    T sum = 0;
    switch( p ) {
    case'*':
        return y*x;
        break;
    case'/':
        return y/x;
        break;
    case'+':
        return y+x;
        break;
    case'-':
        return y-x;
        break;
    default:
        return 0;
        break;
    }
}

int main() {
    char ch[20];
    cout<<"��������ʽ����#�Ž�����"<<endl;
    cin>>ch;
    LinkStack<int> stack1;
    stack1.Process( ch );
    return 0;
}
