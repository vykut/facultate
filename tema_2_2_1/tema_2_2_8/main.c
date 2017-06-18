//
//  main.c
//  tema_2_2_8
//
//  Created by Victor Socaciu on 03/06/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>

int radacina (int v, int *tata)
{
    int u=v;
    while(tata[u]>=0)
        u=tata[u];
    return u;
}

int kruskall(int a[][3],int nm, int nv)
{
    FILE *f=fopen("kruskall.out","wb");
    int tata[50],i,j;
    int v1,v2,k,p,c=0;
    for(i=0;i<nv;i++)
        tata[i]=-1;
    for(j=i=0;i<nv-1;j++)
    {
        v1=a[j][0];
        v2=a[j][1];
        k=radacina(v2,tata);
        p=radacina(v1,tata);
        if(k-p)
        {
            if(tata[k]<tata[p])
            {
                tata[k]+=tata[p];
                tata[p]=k;
            }
            else
            {
                tata[p]+=tata[k];
                tata[k]=p;
            }
            c+=a[j][2];
            //printf("%i -> %i cost %i\n",v1+1,v2+1,a[j][2]);
            v1++;
            v2++;
            fwrite(&v1,sizeof(int),1,f);
            fwrite(&v2,sizeof(int),1,f);
            fwrite(&a[j][2],sizeof(int),1,f);
            v1--;
            v2--;
            i++;
        }
    }
    fclose(f);
    return c;
}

int main(void)
{
    int cost,i,j,nv,nm,a[100][3];
    printf("Numarul de varfuri: ");
    scanf("%i",&nv);
    printf("Numarul de muchii: ");
    scanf("%i",&nm);
    printf("Matricea de reprezentare\n");
    for(i=0;i<nm;i++)
    {
        printf("Muchia %i si ponderea: ",i+1);
        for(j=0;j<3;j++)
            scanf("%i",&a[i][j]);
    }
    for(i=0;i<nm;i++)
        for(j=0;j<2;j++)
            a[i][j]--;
    //printf("Arborele de cost minim:\n");
    cost=kruskall(a,nm,nv);
    //printf("cu costul %i\n",cost);
    FILE *f=fopen("kruskall.out","r+b"),*g=fopen("kruskall.txt","w");
    fseek(f,0,SEEK_END);
    fwrite(&cost,sizeof(int),1,f);
    fclose(f);
    f=fopen("kruskall.out","rb");
    while(!feof(f))
    {
        fread(&i,sizeof(int),1,f);
        fprintf(g,"%i ",i);
    }
    fclose(f);
    fclose(g);
}
