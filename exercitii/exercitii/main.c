#include<stdio.h>
#include<stdlib.h>

int posibil(int *x,int i)
{
    int j, p;
    p=1;
    for(j=0;j<i;j++)
        if(x[i]==x[j] || abs(i-j)==abs(x[i]-x[j]))
            p=0;
    return p;
}

char r;

void retine_solutia(int nr, int n, int *x)
{
    int i,j;
    printf("Solutia numarul %d\n",nr);
    for(i=1;i<=n;i++) {
        for(j=1;j<=n;j++)
            printf("%c ",j==x[i]?'R':'X');
        printf("\n");
    }
    if(r=='n') {
        printf("Urmatoarea (n) sau Ultima (1)? ");
        r=getchar();
    }
}

int regine(int n)
{
    int nr=0, *x, i=1, am;
    x=(int*)calloc((n+1),sizeof(int));
    while(i) {
        am=0;
        while(x[i]<n && !am) {
            x[i]++;
            am=posibil(x,i);
        }
        if(!am)
            i--;
        else
            if(i==n)
                retine_solutia(++nr,n,x);
            else x[++i]=0;
    }
    free(x);
    return nr;
}

int main(void)
{
    int n;
    scanf("%d",&n);
    printf("Numarul de solutii este %d\n",regine(n));
}
