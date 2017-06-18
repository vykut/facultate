//
//  main.c
//  exercitii2
//
//  Created by Victor Socaciu on 18/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define nume1 "vector1.dat"
#define nume2 "vector2.dat"
#define nume3 "interclasare.dat"

long creare(char* nume)
{
    long x;
    FILE *f=fopen(nume,"wb");
    float n;
    for(int i=0;i<5;i++)
    {
        scanf("%f",&n);
        fwrite(&n,sizeof(float),1,f);
    }
    x=ftell(f);
    fclose(f);
    return x;
}
void afisare(char* nume)
{
    FILE *f=fopen(nume,"rb");
    float x;
    while(!feof(f))
    {
        fread(&x,sizeof(float),1,f);
        printf("%.1f ",x);
    }
}
int main()
{
    float x,y;
    long a,b;
    a=creare(nume1);
    printf("%ld\n",a);
    b=creare(nume2);
    FILE *f=fopen(nume3,"wb"),*f1=fopen(nume1,"r+b"),*f2=fopen(nume2,"r+b");
    fread(&x,sizeof(float),1,f1);
    fread(&y,sizeof(float),1,f2);
    while(!feof(f1) && !feof(f2))
        if(x<y)
        {
            fwrite(&x,sizeof(float),1,f);
            if(ftell(f1)<=a)
                fread(&x,sizeof(float),1,f1);
        }
        else
        {
            fwrite(&y,sizeof(float),1,f);
            if(ftell(f)<=b)
                fread(&y,sizeof(float),1,f2);
        }
    while(!feof(f1))
    {
        fwrite(&x,sizeof(float),1,f);
        fread(&x,sizeof(float),1,f1);
    }
    while(!feof(f2))
    {
        fwrite(&y,sizeof(float),1,f);
        fread(&y,sizeof(float),1,f2);
    }
    fclose(f);
    afisare(nume3);
    fclose(f1);
    fclose(f2);
}



















