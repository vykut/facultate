//
//  main.c
//  seminar10
//
//  Created by Victor Socaciu on 03/05/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include "functii_fisiere_relative.h"

#define fisier1 "FisBinRel.dat"
#define fisier2 "FisTextRel.txt"
struct produs
{
    int cod;
    char nume[20];
    int pret;
    int cant[12];
}x;

void creare()
{
    int i;
    FILE *f=fopen(fisier1,"wb");
    printf("Cod produs:");
    scanf("%d",&x.cod);
    while(!feof(stdin))
    {
        fflush(stdin);
        //Preformare(f, sizeof(struct produs), 50);
        printf("Numele produsului: ");
        scanf("%20s",x.nume);
        printf("Pret: ");
        scanf("%d",&x.pret);
        for(i=0;i<12;i++)
        {
            printf("Introduceti cantitatea %d: ",i+1);
            scanf("%d",&x.cant[i]);
        }
        fwrite(&x,sizeof(struct produs),1,f);
        printf("Cod produs:");
        scanf("%d",&x.cod);
        Preformare(f, sizeof(struct produs), 50);
    }
    fclose(f);
}
void listare()
{
    int i;
    FILE *f=fopen(fisier1,"rb"),*g=fopen(fisier2,"w");
    fprintf(g,"%s %s %24s %14s\n\n","Cod","Nume","Pret","Cantitate");
    while(!feof(f))
    {
        CitesteUrmatorul(f, sizeof(struct produs), &x);
        //fread(&x,sizeof(struct produs),1,f);
        fprintf(g,"%d %3s %22d    ",x.cod,x.nume,x.pret);
        for(i=0;i<12;i++)
        {
            fprintf(g,"%2d  ",x.cant[i]);
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
}
int main(void)
{
    creare();
    listare();
}
