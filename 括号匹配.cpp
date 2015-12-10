#include<stdio.h>
int main()
{
    //freopen("test.txt","r",stdin);
    char s[10005],left[10005];
    int n;
    scanf("%d",&n);
    getchar();
    while(n--) {
        gets(s);
        int flag = 1;
        int len = 0;
        for(int i=0; s[i] && flag; i++) {
            switch(s[i]) {
            case '(':
            case '[':
            case '{':
                left[len++]=s[i];
                break;
            case ')':
                if(len==0 || left[--len]!='(') flag=0;
                break;
            case ']':
                if(len==0 || left[--len]!='[') flag=0;
                break;
            case '}':
                if(len==0 || left[--len]!='{') flag=0;
                break;
            }
        }
        if(len==0 && flag)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}
