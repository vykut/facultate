//
//  main.c
//  tema_2_2_5
//
//  Created by Victor Socaciu on 04/06/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>

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

float determinant()
{
    float det=1,x;
    FILE *f=fopen("matrice.dat","rb");
    int m,n,i,j;
    fread(&m,sizeof(int),1,f);
    fseek(f,0,SEEK_END);
    n=(ftell(f)-sizeof(int))/(m*sizeof(float));
    fseek(f,0,SEEK_SET);
    for(i=1;i<m;i++)
    {
        fseek(f,sizeof(int)+i*n*sizeof(float),SEEK_SET);
        for(j=0;j<i;j++)
        {
            fread(&x,sizeof(float),1,f);
            if(x!=0)
                return 0;
        }
    }
    for(i=0;i<m;i++)
        {
            fseek(f,sizeof(int)+(i*n+i)*sizeof(float),SEEK_SET);
            fread(&x,sizeof(float),1,f);
            det*=x;
        }
    return det;
}
int main(void)
{
    creare_matrice();
    printf("%.2f",determinant());
}
