//
//  main.c
//  exercitii1
//
//  Created by Victor Socaciu on 12/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>

#define nume1 "Vector.dat"
#define nume2 "Aparitii.dat"
void creare()
{
    float element;
    FILE *f=fopen(nume1,"wb");
    while(!feof(stdin))
    {
        scanf("%f",&element);
        fwrite(&element,sizeof(float),1,f);
    }
    fclose(f);
}
void afisare()
{
    int i;
    FILE *f=fopen(nume2,"rb");
    while(!feof(f))
    {
        fread(&i,sizeof(int),1,f);
        printf("%d ",i);
    }
    fclose(f);
}
int main(void)
{
    creare();
    FILE *f=fopen(nume1,"rb"),*g=fopen(nume2,"wb");
    float max,element;
    fread(&max,sizeof(float),1,f);
    int ok=1,i;
    fwrite(&ok,sizeof(int),1,g);
    while(!feof(f))
    {
        fread(&element,sizeof(float),1,f);
        if(element>max && !feof(f))
        {
            fseek(g,0,SEEK_SET);
            //rewind(f);
            ok=0;
            for(i=1;i<(ftell(f)/sizeof(float));i++)
                fwrite(&ok,sizeof(int),1,g);
            max=element;
        }
        if(element==max && !feof(f))
        {
            ok=1;
            fwrite(&ok,sizeof(int),1,g);
        }
        if(element<max && !feof(f))
        {
            ok=0;
            fwrite(&ok,sizeof(int),1,g);
        }
    }
    fclose(f);
    fclose(g);
    afisare();
}
