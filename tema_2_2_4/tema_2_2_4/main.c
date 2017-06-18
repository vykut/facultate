//
//  main.c
//  tema_2_2_4
//
//  Created by Victor Socaciu on 04/06/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void creare_vector()
{
    FILE *f=fopen("vector.dat","wb");
    float x;
    while(!feof(stdin))
    {
        scanf("%f",&x);
        fwrite(&x,sizeof(float),1,f);
    }
    fclose(f);
}

void creare_matrice()
{
    FILE *f=fopen("matrice.dat","wb");
    int y;
    float x;
    scanf("%d",&y);
    fwrite(&y,sizeof(int),1,f);
    while(!feof(stdin))
    {
        scanf("%f",&x);
        fwrite(&x,sizeof(float),1,f);
    }
    fclose(f);
}

float* produs()
{
    FILE *f=fopen("vector.dat","rb"),*g=fopen("matrice.dat","rb");
    int m,n,i,j;
    float *v = NULL,x,y;
    fread(&m,sizeof(int),1,g);
    v=(float*)calloc(m,sizeof(float));
    fseek(g,0,SEEK_END);
    n=(ftell(g)-sizeof(int))/(m*sizeof(float));
    fseek(g,0,SEEK_SET);
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            fread(&x,sizeof(float),1,f);
            fseek(g,sizeof(int)+(i+j*n)*sizeof(float),SEEK_SET);
            fread(&y,sizeof(float),1,g);
            v[i]+=x*y;
        }
        rewind(f);
    }
    fclose(f);
    fclose(g);
    return v;
    
}

int main(void)
{
    int i;
    //creare_vector();
    //creare_matrice();
    float *v;
    v=produs();
    for(i=0;i<3;i++)
        printf("%4.2f  ",v[i]);
}
