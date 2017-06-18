//
//  main.c
//  exercitii6
//
//  Created by Victor Socaciu on 23/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define mat1 "matrice1.dat"
#define mat2 "matrice2.dat"
#define rez "produs_matrice.dat"

void creare(char* nume)
{
    int m;
    float x;
    FILE *f=fopen(nume,"wb");
    printf("Introduceti nr de linii pt matricea %s: ",nume);
    scanf("%d",&m);
    fwrite(&m,sizeof(int),1,f);
    printf("Introduceti elementele: ");
    while(!feof(stdin))
    {
        scanf("%f",&x);
        fwrite(&x,sizeof(float),1,f);
    }
    fclose(f);
}
void afisare(char* nume)
{
    int m,n,i,j;
    float x;
    FILE *f=fopen(nume,"rb");
    fread(&m,sizeof(int),1,f);
    //printf("%d\n",m);
    fseek(f,0,SEEK_END);
    n=((int)ftell(f)-sizeof(int))/(m*sizeof(float));
    fseek(f,sizeof(int),SEEK_SET);
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            fread(&x,sizeof(float),1,f);
            printf("%.1f\t",x);
        }
        printf("\n");
    }
}
int main(void)
{
    //creare(mat1);
    creare(mat2);
    int m,n,i,j,p,k,l;
    float a,b,s;
    FILE *f1=fopen(mat1,"rb"),*f2=fopen(mat2,"rb"),*fr=fopen(rez,"wb");
    fread(&m,sizeof(int),1,f1);
    fseek(f1,0,SEEK_END);
    p=((int)ftell(f1)-sizeof(int))/(m*sizeof(float));
    fread(&n,sizeof(int),1,f2);
    fseek(f2,0,SEEK_END);
    l=((int)ftell(f2)-sizeof(int))/(n*sizeof(float));
    if(p!=n)
        return 0;
    else
    {
        n=l;
        fwrite(&m,sizeof(int),1,fr);
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
            {
                s=0;
                fseek(f1,i*sizeof(float)*p+sizeof(int),SEEK_SET);
                for(k=0;k<p;k++)
                {
                    fread(&a,sizeof(float),1,f1);
                    //printf("%.0f ",a);
                    fseek(f2,p*j*sizeof(float)+sizeof(int)+k*sizeof(float),SEEK_SET);
                    fread(&b,sizeof(float),1,f2);
                    //printf("%.0f ",b);
                    s+=a*b;
                }
                //printf("%.0f\t",s);
                fwrite(&s,sizeof(float),1,fr);
            }
    }
    fclose(f1);
    fclose(f2);
    fclose(fr);
    afisare(rez);
    return 1;
    
}
