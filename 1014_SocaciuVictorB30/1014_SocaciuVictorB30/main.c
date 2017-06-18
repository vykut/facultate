//
//  main.c
//  1014_SocaciuVictorBxx
//
//  Created by Victor Socaciu on 26/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//  nisioiucodrin@gmail.com
//  1014_SocaciuVictorB30

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
struct STUDENT
{
    int nr;
    char nume[30];
    int grupa;
    char punctaj[3];
    char  puncte_tema[10];
    char punctaj_examen[2];
}x,y;

void creare()
{
    int i;
    FILE *f=fopen("Studenti.dat","wb");
    printf("Introduceti nr. Matricol:");
    scanf("%d",&x.nr);
    while(!feof(stdin))
    {
        fflush(stdin);
        //fgetc(stdin);
        printf("Introduceti numele studentului: ");
        fgets(x.nume,30,stdin);
        printf("Introduceti grupa: ");
        scanf("%d",&x.grupa);
        printf("Introduceti punctajul la proba practica (0-30): ");
        //fgetc(stdin);
        fgets(x.punctaj,3,stdin);
        //fgetc(stdin);
        for(i=0;i<10;i++)
        {
            printf("Introduceti nota la tema %d (0-1): ",i+1);
            //fgetc(stdin);
            scanf("%c",&x.puncte_tema[i]);
        }
        printf("Introduceti punctajul la examen (0-50): ");
        //fgetc(stdin);
        fgets(x.punctaj_examen,3,stdin);
        //fgetc(stdin);
        fwrite(&x,sizeof(struct STUDENT),1,f);
        printf("Introduceti nr. Matricol:");
        scanf("%d",&x.nr);
    }
    fclose(f);
}
void sortare()
{
    int ok=1;
    FILE *f=fopen("Studenti.dat","r+b");
    while(ok)
    {
        ok=0;
        fread(&x,sizeof(struct STUDENT),1,f);
        while(!feof(f))
        {
            fread(&y,sizeof(struct STUDENT),1,f);
            if(x.grupa>y.grupa)
            {
                ok=0;
                fseek(f,ftell(f)-2*sizeof(struct STUDENT),SEEK_SET);
                fwrite(&y,sizeof(struct STUDENT),1,f);
                fwrite(&x,sizeof(struct STUDENT),1,f);
            }
            x=y;
        }
        rewind(f);
    }
    fclose(f);
}
int grupa()
{
    int i,nr=0,max=0,s=0;
    FILE *f=fopen("Studenti.dat","rb");
    fread(&x,sizeof(struct STUDENT),1,f);
    while(!feof(f))
    {
        fread(&y,sizeof(struct STUDENT),1,f);
        if(x.grupa==y.grupa)
        {
            s=atoi(x.punctaj);
            //printf("%d ",s);
            for(i=0;i<10;i++)
                s=s+atoi(&x.puncte_tema[i]);
            //printf("%d ",s);
            s=s+atoi(x.punctaj_examen);
            //printf("%d ",s);
            s+=10;
            //printf("%d ",s);
            if(s<40)
                nr++;
        }
        else
        {
            s=atoi(x.punctaj);
            for(i=0;i<10;i++)
                s+=atoi(&x.puncte_tema[i]);
            s+=atoi(x.punctaj_examen);
            s+=10;
            if(s<40)
                nr++;
            if(nr>max)
            max=x.grupa;
            nr=0;
        }
        x=y;
        s=0;
    }
    fclose(f);
    return max;
}
void afisare()
{
    int i;
    FILE *f=fopen("lista.txt","w"),*g=fopen("Studenti.dat","rb");
    fprintf(f,"%s %s %21s %s %6s %29s\n","Nr.","Nume","Grupa","Punctaj","Note teme","Punctaj examen");
    while(!feof(g))
    {
        fread(&x,sizeof(struct STUDENT),1,g);
        fprintf(f,"%2d %20s %6d %7s ",x.nr,x.nume,x.grupa,x.punctaj);
        for(i=0;i<10;i++)
            fprintf(g,"%20c",x.puncte_tema[i]);
        fprintf(f,"%2s",x.punctaj_examen);
    }
    fclose(f);
    fclose(g);
}
int main()
{
    creare();
    sortare();
    printf("Grupa cu cei mai multi studenti cu punctaj sub 40 este: %d",grupa());
    afisare();
    
}
