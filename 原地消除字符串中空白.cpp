/**题目：实现原地消除字符串的空白（例："aa   c    d e " => "aacde"）
   扩展：原地消除字符串的重复空白（例："aa  c  d e " => "aa c d e"）
 **/

#include<stdio.h>

//删除字符数组str中的所有某个特定字符del
char * delChar(char* str, char del = ' ')
{
	//防止传入无效参数-空指针
	if(str==0 || *str==0 || del==0)
		return str;
	char *pLeft=str, *pRight=str;
	while(*pRight!=0 && *pRight!=del)
		++pRight;
	pLeft = pRight;//第一个要删的位置
	while(*pRight==del) //跳过要删除的元素
		++pRight;
	//当前pRight指向第一个要向前移动的元素
	for(;*pRight!=0;++pRight) {
		//*pRight不需要删除则向前复制元素
		if(*pRight!=del) {
			*pLeft = *pRight;
			++pLeft;
		}
	}
	//最后一位置0，否则尾部可能有上一次的残留字符
	*pLeft = 0;
	return str;
}
//删除字符数组str中的所有某个特定字符del
char * delChar2(char* str, char del = ' ')
{
	//防止传入无效参数-空指针
	if(str==0 || *str==0 || del==0)
		return str;
	char *pLeft=str, *pRight=str;
	//一直遍历到字符串尾部
	for(;*pRight!=0;++pRight) {
		//*pRight到达第一个不需要删除的元素
		if(*pRight!=del) {
			//不指向同一元素
			if(pLeft!=pRight)
				*pLeft = *pRight;
			++pLeft;
		}
	}
	//最后一位置0，否则尾部可能有上一次的残留字符
	*pLeft = 0;
	return str;
}
//删除字符数组str中的所有连续重复的某个特定字符del
char * delRepeatedChar(char* str, char del = ' ')
{
	//防止传入无效参数-空指针
	if(str==0 || *str==0 || del==0)
		return str;
	char *pLeft=str, *pRight=str;
	while(*pRight!=0 && *pRight!=del)
		++pRight;
	pLeft = pRight;//第一个 所指元素是要删除的字符
	for(; *pRight!=0; ++pLeft, ++pRight) {
		//pRight所指元素是要删除的字符
		if(*pRight==del) {
			//下一个元素也是要删除的字符，则删除下一个字符
			if(*(pRight+1)==del){
				*pLeft++ = *pRight;
				//移动到当前需要向前复制的位置
				while(*pRight==del)
					++pRight;
				//复制元素
				*pLeft = *pRight;
				continue;
			}
		}
		//复制元素
		*pLeft = *pRight;
	}
	//最后一位置0，否则尾部可能有上一次的残留字符
	*pLeft = 0;
	return str;
}

int main()
{
	char str[128] = "   a c b  cccd f  ghh jk lmnnn qr     st ";
	char del = 'c';
	printf("请输入一个源字符串:");
	while(gets(str)) {	//一定要用gets而不是scanf,因为可能包含空格
		printf("请输入一个要删除的字符:");
		del = getchar();
		printf("<%s> 删除连续的字符'%c'后:\n",str,del);
		printf("<%s>\n\n请输入一个源字符串:",delRepeatedChar(str,del));
		getchar();
	}
	return 0;
}
