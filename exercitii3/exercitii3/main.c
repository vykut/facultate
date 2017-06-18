//
//  main.c
//  exercitii3
//
//  Created by Victor Socaciu on 20/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define nume "numere.dat"
#define nume1 "numere2.dat"
void creare()
{
    FILE *f=fopen(nume,"wb");
    float x;
    while(!feof(stdin))
    {
        scanf("%f",&x);
        fwrite(&x,sizeof(float),1,f);
    }
    fclose(f);
}
int main(void)
{
    //creare();
    FILE *f=fopen(nume,"rb"),*g=fopen(nume1,"wb");
    float a,b,x;
    scanf("%f%f",&a,&b);
    while(!feof(f))
    {
        fread(&x,sizeof(float),1,f);
        if(x<a || x>b)
            fwrite(&x,sizeof(float),1,g);
    }
    fclose(f);
    fclose(g);
    remove(nume);
    rename("numere2.dat",nume);
    f=fopen(nume,"rb");
    while(!feof(f))
    {
        fread(&x,sizeof(float),1,f);
        printf("%.1f ",x);
    }
    fclose(f);
}
