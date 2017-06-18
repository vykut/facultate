//
//  main.c
//  2.3.4
//
//  Created by Victor Socaciu on 23/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nume1 "impozite_sector_1.dat"
#define nume2 "impozite_sector_2.dat"
#define nume3 "impozite_oras.dat"
struct CONTRIBUABIL
{
    char CNP[13];
    char nume[30];
    char adresa[50];
    float ic;
    float ip;
}x,y;

void creare(char *nume)
{
    FILE *f=fopen(nume,"wb");
    printf("Introduceti CNP-ul: ");
    scanf("%s",x.CNP);
    getchar();
    while(!feof(stdin))
    {
        fflush(stdin);
        printf("Introduceti numele: ");
        scanf("%[^\n]%*c",x.nume);
        printf("Introduceti adresa: ");
        scanf("%[^\n]%*c",x.adresa);
        printf("Introduceti impozitul calculat: ");
        scanf("%f",&x.ic);
        printf("Introduceti impozitul platit: ");
        scanf("%f",&x.ip);
        fwrite(&x,sizeof(struct CONTRIBUABIL),1,f);
        printf("Introduceti CNP-ul: ");
        scanf("%s",x.CNP);
        getchar();
    }
    fclose(f);
}

void sortare(char *nume)
{
    FILE *f=fopen(nume,"r+b");
    int ok=1;
    while(ok)
    {
        ok=0;
        fread(&x,sizeof(struct CONTRIBUABIL),1,f);
        while(!feof(f))
        {
            fread(&y,sizeof(struct CONTRIBUABIL),1,f);
            if(x.ic>y.ic)
            {
                ok=1;
                fseek(f,ftell(f)-2*sizeof(struct CONTRIBUABIL),SEEK_SET);
                fwrite(&y,sizeof(struct CONTRIBUABIL),1,f);
                fwrite(&x,sizeof(struct CONTRIBUABIL),1,f);
            }
            x=y;
        }
        rewind(f);
    }
    fclose(f);
}

void afisare(char* nume)
{
    FILE *f=fopen(nume,"rb");
    while(!feof(f))
    {
        fread(&x,sizeof(struct CONTRIBUABIL),1,f);
        printf("%s\n",x.CNP);
        printf("%s\n",x.nume);
        printf("%s\n",x.adresa);
        printf("Impozitul calculat este: %.1f\n",x.ic);
        printf("Impozitul platit este: %.1f\n\n",x.ip);
    }
    fclose(f);
}
int main(void)
{
    //creare(nume1);
    //creare(nume2);
    sortare(nume1);
    sortare(nume2);
    //afisare(nume2);
    FILE *f1=fopen(nume1,"rb"),*f2=fopen(nume2,"rb"),*f3=fopen(nume3,"wb");
    fread(&x,sizeof(struct CONTRIBUABIL),1,f1);
    fread(&y,sizeof(struct CONTRIBUABIL),1,f2);
    if(x.ic>y.ic)
    {
        fwrite(&y,sizeof(struct CONTRIBUABIL),1,f3);
        fread(&y,sizeof(struct CONTRIBUABIL),1,f2);
    }
    else
    {
        fwrite(&x,sizeof(struct CONTRIBUABIL),1,f3);
        fread(&x,sizeof(struct CONTRIBUABIL),1,f1);
    }
    while(!feof(f1) && !feof(f2))
        if(x.ic>y.ic)
        {
            fwrite(&y,sizeof(struct CONTRIBUABIL),1,f3);
            fread(&y,sizeof(struct CONTRIBUABIL),1,f2);
        }
        else
        {
            fwrite(&x,sizeof(struct CONTRIBUABIL),1,f3);
            fread(&x,sizeof(struct CONTRIBUABIL),1,f1);
        }
    while(!feof(f1))
    {
        fwrite(&x,sizeof(struct CONTRIBUABIL),1,f3);
        fread(&x,sizeof(struct CONTRIBUABIL),1,f1);
    }
    while(!feof(f2))
    {
        fwrite(&y,sizeof(struct CONTRIBUABIL),1,f3);
        fread(&y,sizeof(struct CONTRIBUABIL),1,f2);
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    afisare(nume3);
}






