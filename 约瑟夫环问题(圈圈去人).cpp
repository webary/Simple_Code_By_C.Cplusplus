/** 掌握顺序表的存储结构以及基本运算的实现。
 * 约瑟夫环问题：设编号为1，2，3，……，n的n(n>0)个人按顺时针方向围坐一圈，m为任意一个正整数。
 * 从第一个人开始顺时针方向自1起顺序报数，报到m时停止并且报m的人出列，再从他的下一个人开始重新从1报数，
 * 报到m时停止并且报m的人出列。如此下去，直到所有人全部出列为止。要求设计一个程序模拟此过程，
 * 对任意给定的m和n，求出出列编号序列。
 */

#include<stdio.h>
#include<malloc.h>
#define MaxSize 50
typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
	int length;
}SqList;
void InitList(SqList *&L){      //初始化顺序表
	L=(SqList *)malloc(sizeof(SqList));
	L->length=0;
}
void CreateList(SqList *&L,int n){      //创建顺序表
	for(int i=0;i<n;i++)
		L->data[i]=i+1;
	L->length=n;
}
void DispList(SqList *L){            //输出顺序表，用来检测创建的顺序表是否符合要求
	int i;
	for(i=0;i<L->length;i++)
		printf("%d  ",L->data[i]);
	printf("\n");
}
bool GetElem(SqList *L,int i,ElemType &e){     //求顺序表中第i号元素值
	if(i<0||i>L->length-1)
		return false;
	e=L->data[i];
	return true;
}
bool ListDelete(SqList *&L,int i,ElemType &e){     //删除第i号元素
	int j;
	if(i<0||i>L->length-1)
		return false;
	e=L->data[i];
	for(j=i;j<L->length-1;j++)
		L->data[j]=L->data[j+1];
	L->length--;
	return true;
}

int main(){
	int m,n,i,j,t=0;
	SqList *L;
	ElemType e;
	printf("输入n的值: ");
	scanf("%d",&n);
	printf("初始化顺序表...\n");
	InitList(L);
	printf("创建一个有元素的顺序表...\n");
	CreateList(L,n);
	printf("\n输出顺序表:\n");
	DispList(L);
	printf("\n输入m的值: ");
	scanf("%d",&m);
	puts("输出编号序列为：");
	for(i=n;i>=1;i--){
		t=(t+m-1)%i;
		GetElem(L,t,e);
		printf("%d  ",e);
        ListDelete(L,t,e);
	}
	printf("\n");
	return 0;
}
