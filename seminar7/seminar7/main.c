//
//  main.c
//  seminar7
//
//  Created by Victor Socaciu on 05/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct STUDENT
{
    int nr;
    char nume[30];
    int an;
    int grupa;
    int n;
    int note[15];
}x;
int main()
{
    //CREARE FISIER CU DATE STUDENTI
    
    //FILE *f=fopen("studenti.out","wb");
    /*while(!feof(stdin))
    {
        int i;
        printf("Introduceti numarul matricol: ");
        scanf("%d",&x.nr);
        while(!feof(stdin))
        {
            fflush(stdin);
            printf("Introduceti numele: ");
            fgetc(stdin);
            fgets(x.nume, sizeof(x.nume), stdin);
            printf("Introduceti anul: ");
            scanf("%d",&x.an);
            printf("Introduceti grupa: ");
            scanf("%d",&x.grupa);
            printf("Introduceti numarul de note: ");
            scanf("%d",&x.n);
            for(i=0;i<x.n;i++)
            {
                printf("Introduceti nota %d: ",i+1);
                scanf("%d",x.note+i);
            }
            fwrite(&x,sizeof(struct STUDENT),1,f);
            printf("Introduceti numarul matricol: ");
            scanf("%d",&x.nr);
        }
        fclose(f);
    }*/
    
    //ACTUALIZARE NOTA FILOSOFIE
    
    FILE *f=fopen("studenti.out","r+b");
     int grupa,i;
    while(!feof(stdin))
    {
        printf("Introduceti grupa: ");
        scanf("%d",&grupa);
        for(i=0;i<6;i++)
        {
            fread(&x,sizeof(struct STUDENT),1,f);
            if(grupa==x.grupa)
            {
                if(x.note[0]<10)
                {
                    x.note[0]+=1;
                    fseek(f,ftell(f)-sizeof(struct STUDENT),0);
                    fwrite(&x,sizeof(struct STUDENT),1,f);
                    printf("S-a adaugat punctul din oficiu pentru studentul: %s",x.nume);
                }
                else
                    printf("Studentul %s are deja nota 10.",x.nume);
            }
        }
        rewind(f);
    }
    fclose(f);
}
