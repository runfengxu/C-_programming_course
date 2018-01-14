#include<stdio.h>
#include<stdlib.h>

int gcd(int a,int b)
{
    int i,x=a,y=b;
    for(i=0;x!=y;i++)
    {
        x=a<b?a:b;
        y=(a>b?a:b)-(a<b?a:b);
        a=x;
        b=y;
    }
    return x;
}

int main(int argc,char *argv[])
{
    int l;
    l=gcd(atoi(argv[1]),atoi(argv[2]));
    printf("the gcd of %s and %s is %d\n",argv[1],argv[2],l);
    return 0;
}
