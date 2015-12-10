#include<stdio.h>
#include<string.h>
char* formatString(char *sourceString) {
    //防止传入无效参数-空指针
    if(sourceString==0 || *sourceString==0)
        return sourceString;
    char *pLeft=sourceString, *pRight=sourceString, del = ' ';
    while(*pLeft!=0 && *pLeft==del) //找到第一个不为空格的位置
        ++pLeft;
    if(*pLeft==0) //整个字符串都是空格
        return "";
    int len = strlen(sourceString);
    pRight = sourceString + len - 1;
    while(*pRight==del) //找到最后一个非空格的位置
        --pRight;
    for(int i=0;i<pRight-pLeft+1;++i) //把首尾空格去掉后把中间的字符移动到字符串开头位置
        sourceString[i] = sourceString[i+pLeft-sourceString];
    sourceString[pRight-pLeft+1] = '\0';
    //下面删除连续的空格
    pRight=sourceString;
    while(*pRight!=0 && *pRight!=del)
        ++pRight;
    pLeft = pRight;//第一个所指元素是要删除的字符
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
    return sourceString;
}
char * delRepeatedChar(char* str, char del);
int main()
{
    char str[128] = "   a c b  cccd f  ghh jk lmnnn qr     st ";
    char del = 'c';
    printf("请输入一个源字符串:");
    while(gets(str)) {    //一定要用gets而不是scanf,因为可能包含空格
        printf("请输入一个要删除的字符:");
        printf("<%s>\n",formatString(str));
        //del = getchar();
        //printf("<%s> 删除连续的字符'%c'后:\n",str,del);
        //printf("<%s>\n\n请输入一个源字符串:",delRepeatedChar(str,del));
        getchar();
    }
    return 0;
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
