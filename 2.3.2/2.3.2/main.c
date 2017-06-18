//
//  main.c
//  2.3.2
//
//  Created by Victor Socaciu on 23/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define fis "studenti.dat"
struct STUDENT
{
    char nume[30];
    int an;
    int grupa;
    int nr_discipline;
    int n;
    int note[15];
}x,y;

void creare()
{
    
    FILE *f=fopen(fis,"wb");
    int i;
    printf("Introduceti numele studentului: ");
    scanf("%s",x.nume);
    while(!feof(stdin))
    {
        printf("Introduceti anul: ");
        scanf("%d",&x.an);
        printf("Introduceti grupa: ");
        scanf("%d",&x.grupa);
        printf("Introduceti nr. de discipline: ");
        scanf("%d",&x.nr_discipline);
        printf("Introduceti nr. de note: ");
        scanf("%d",&x.n);
        for(i=0;i<x.n;i++)
        {
            printf("Introduceti nota %d: ",i+1);
            scanf("%d",&x.note[i]);
        }
        fwrite(&x,sizeof(struct STUDENT),1,f);
        printf("Introduceti numele studentului: ");
        scanf("%s",x.nume);
    }
    fclose(f);
}

void afisare()
{
    int i;
    FILE *f=fopen(fis,"rb");
    while(!feof(f))
    {
        fread(&x,sizeof(struct STUDENT),1,f);
        printf("%s\t",x.nume);
        printf("Anul: %d\t",x.an);
        printf("Grupa: %d\t",x.grupa);
        printf("Nr discipline: %d\t",x.nr_discipline);
        printf("Note: ");
        for(i=0;i<x.n;i++)
            printf("%d ",x.note[i]);
        printf("\n");
    }
    fclose(f);
}
int main(void)
{
    int ok=1;
    creare();printf("\n\n");
    FILE *f=fopen(fis,"r+b");
    while(ok==1)
    {
        ok=0;
        fread(&x,sizeof(struct STUDENT),1,f);
        while(!feof(f))
        {
            fread(&y,sizeof(struct STUDENT),1,f);
            if(x.an==y.an)
            {
                if(x.grupa==y.grupa)
                {
                    if(strcmp(x.nume,y.nume)>0)
                    {
                        fseek(f,ftell(f)-2*sizeof(struct STUDENT),SEEK_SET);
                        fwrite(&y,sizeof(struct STUDENT),1,f);
                        fwrite(&x,sizeof(struct STUDENT),1,f);
                        x=y;
                        ok=1;
                    }
                }
                else
                if(x.grupa>y.grupa)
                {
                    fseek(f,ftell(f)-2*sizeof(struct STUDENT),SEEK_SET);
                    fwrite(&y,sizeof(struct STUDENT),1,f);
                    fwrite(&x,sizeof(struct STUDENT),1,f);
                    x=y;
                    ok=1;
                }
            }
            else
            if(x.an>y.an)
            {
                fseek(f,ftell(f)-2*sizeof(struct STUDENT),SEEK_SET);
                fwrite(&y,sizeof(struct STUDENT),1,f);
                fwrite(&x,sizeof(struct STUDENT),1,f);
                x=y;
                ok=1;
            }
            x=y;
        }
        rewind(f);
    }
    fclose(f);
    afisare();
}
