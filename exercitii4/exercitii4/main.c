//
//  main.c
//  exercitii4
//
//  Created by Victor Socaciu on 20/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>

#define nume "matrice.dat"

void creare()
{
    FILE *f=fopen(nume,"wb");
    int m,n;
    float x;
    scanf("%d%d",&m,&n);
    fwrite(&m,sizeof(int),1,f);
    fwrite(&n,sizeof(int),1,f);
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
    {
        scanf("%f",&x);
        fwrite(&x,sizeof(float),1,f);
    }
    fclose(f);
}
int main(void)
{
    int m,n,i,j;
    float x,y;
    creare();
    FILE *f=fopen(nume,"rb");
    fread(&m,sizeof(int),1,f);
    fread(&n,sizeof(int),1,f);
    for(i=0;i<m;i++)
    {
        fread(&x,sizeof(float),1,f);
        for(j=0;j<n-1;j++)
        {
            fread(&y,sizeof(float),1,f);
            if(x>y)
                j=n-1;
            else
                x=y;
        }
        if(x==y)
            printf("%d ",i+1);
    }
    printf("\n");
    fclose(f);
    
}
