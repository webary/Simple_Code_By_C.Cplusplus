#include<math.h>
#include<stdio.h>
#include<time.h>

bool isPrime(int n)
{
    if(n<2)
        return 0;
    int k=sqrt(n),i;
    for(i=2; i<=k; i++)
        if(n%i==0)
            return 0;
    return 1;
}

bool isPrime2(int n)
{
    if(n<2)
        return 0;
    if(n==2)
        return 1;
    int k=sqrt(n),i;
    for(i=3; i<=k; i+=2)
        if(n%i==0)
            return 0;
    return 1;
}

int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    int n=0, prime[10000];
    int t1=clock();
    for(int i=2; i<1000000; i++)
        if(isPrime(i))
            prime[n++]=i;
    printf("用时：%d\t素数个数：%d\n",clock()-t1,n);
    return 0;
}
