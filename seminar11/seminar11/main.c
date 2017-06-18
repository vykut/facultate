//
//  main.c
//  seminar11
//
//  Created by Victor Socaciu on 10/05/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "index.h"
#include "tipuri.h"


void listare()
{
    int i;
    //Extinde();
    Open_index();
    TFISIER g=fopen("Studenti.txt","w");
    rewind(ind);
    fprintf(g,"\n%-10s %-35s Grupa An Note\n","Cod matr.","Nume si prenume");
    ReadSec(&x);
    while(!feof(ind))
    {
        //fprintf(g,"\n%-10s %-35s Grupa An Note\n","Cod matr.","Nume si prenume");
        fprintf(g,"\n%9s. %35s %5d %2d ",x.cheie, x.numestud, x.grupa, x.an);
        for(i=0;i<x.nr;i++)
            fprintf(g,"%2d ",x.note[i]);
        ReadSec(&x);
    }
    fclose(g);
    Close_index();
}

void creare()
{
    int i;
    //scanf("%10s",nume);
    //Extinde();
    New_index();
    printf("Introduceti nr. matricol: ");
    scanf("%10s",x.cheie);
    while(!feof(stdin))
    {
        fflush(stdin);
        printf("Introduceti numele studentului: ");
        scanf("%30s",x.numestud);
        printf("Introduceti anul: ");
        scanf("%d",&x.an);
        printf("Introduceti grupa: ");
        scanf("%d",&x.grupa);
        printf("Introduceti nr. de note: ");
        scanf("%d",&x.nr);
        for(i=0;i<x.nr;i++)
        {
            printf("Introduceti nota %d: ",i+1);
            scanf("%d",&x.note[i]);
        }
        //fwrite(&x,sizeof(STUDENT),1,f);
        if(WriteKey(x))
            printf("\nArticolul a fost adaugat!\n");
        else
            printf("\nCheie invalida\n");
        printf("Introduceti nr. matricol: ");
        scanf("%10s",x.cheie);
    }
    Close_index();
    
}

void pb_3()
{
    int i;
    //Extinde();
    Open_index();
    TCHEIE c;
    while(!feof(stdin))
    {
        printf("Introduceti nr. matricol: ");
        scanf("%10s",c);
        if(SeekKey(c))
        { ReadSec(&x); /*citirea următorului articol în acces secvenţial*/
            
            printf("\nAm gasit studentul:\n");
            
            printf("\nNume : %-35s",x.numestud);
            
            printf("\nCod matricol: %-10s",x.cheie);
            
            printf("\nAn si grupa : %2d / %4d",x.an,x.grupa);
            
            printf("\nNote : ");
            
            for(i=0;i<x.nr;i++)
                printf("%2d ",x.note[i]);
            
            printf("\n");
            
        }
        else
            printf("\nNu e inregistrat un cursant cu acest cod matricol.\n");
    }
    Close_index();
}

void pb_4()
{
    //Extinde();
    Open_index();
    TCHEIE c;
    while(!feof(stdin))
    {
    printf("Introduceti nr. matricol: ");
    scanf("%10s",c);
    if(SeekKey(c))
    { ReadSec(&x);
        if(x.nr<20)
        {
            printf("Introduceti nota: ");
            scanf("%d",&x.note[x.nr++]);
            RewriteKey(x);
            printf("\nS-a introdus nota!\n");
        }
    }
    else
        printf("\nNu e inregistrat un cursant cu acest cod matricol.\n");
    }
}
int main(void) {
    printf("Introduceti numele fisierului: ");
    scanf("%10s",nume);
    Extinde();
    //creare();
    listare();
    //pb_3();
    //pb_4();
    return 0;
}
