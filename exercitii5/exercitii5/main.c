//
//  main.c
//  exercitii5
//
//  Created by Victor Socaciu on 23/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define nume "matrice.dat"

void creare()
{
    int m;
    float x;
    FILE *f=fopen(nume,"wb");
    scanf("%d",&m);
    fwrite(&m,sizeof(int),1,f);
    while(!feof(stdin))
    {
        scanf("%f",&x);
        fwrite(&x,sizeof(float),1,f);
    }
    fclose(f);
}

int main(void)
{
    int m,n;
    float x,sumap=0,sumas=0;
    creare();
    FILE *f=fopen(nume,"rb");
    fread(&m,sizeof(float),1,f);
    n=m;
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        {
            fread(&x,sizeof(float),1,f);
            if(i==j)
                sumap+=x;
            if(j==n-i-1)
                sumas+=x;
        }
    printf("%.1f\t%.1f\n",sumap,sumas);
    //fseek(f,0,SEEK_END);
    //n=((int)ftell(f)-sizeof(int))/(sizeof(float)*m);
    
}
