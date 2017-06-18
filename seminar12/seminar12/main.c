//
//  main.c
//  seminar12
//
//  Created by Victor Socaciu on 17/05/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int** creare_mat(int n)
{
    int i;
    int **mat;
    mat=(int**)calloc(n,sizeof(int*));
    for(i=0;i<n;i++)
        mat[i]=(int*)calloc(n,sizeof(int));
    return mat;
}
void afisare_vector(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d, ",v[i]+1);
    printf("\n");
}
int main(void)
{
    int m,n,i,j,k,nod_plecare,ok=1;
    int **mat,*viz;
    printf("Introduceti nr de noduri: ");
    scanf("%d",&n);
    printf("Introduceti nr de muchii: ");
    scanf("%d",&m);
    mat=creare_mat(n);
    for(k=0;k<m;k++)
    {
        printf("x=");
        scanf("%d",&i);
        printf("y=");
        scanf("%d",&j);
        mat[i-1][j-1]=1;
        mat[j-1][i-1]=1;
    }
    viz=(int*)calloc(n,sizeof(int));
    //afisare_vector(viz,n);
    printf("Introduceti nodul de plecare: ");
    scanf("%d",&nod_plecare);
    k=1;
    viz[nod_plecare-1]=k++;
    j=nod_plecare-1;
    while(ok)
    {
        ok=0;
        for(i=0;i<n;i++)
            if(mat[j][i]==1)
            {
                viz[i]=k++;
            }
        for(i=0;i<n && viz[i]!=0;i++)
        {}
        if(viz[i]==0)
        {
            j=i;
            ok=1;
        }
    }
        afisare_vector(viz,n);
}

