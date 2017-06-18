//
//  main.c
//  seminar8
//
//  Created by Victor Socaciu on 12/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>

#define fisiertext "medie.txt"
#define fisierbinar "Studenti.dat"
#define freadb(x,f) fread(&(x),sizeof(struct STUDENT),1,(f))
#define fwriteb(x,f) fwrite(&(x),sizeof(struct STUDENT),1,(f))


struct STUDENT
{
    int nr;
    char nume[30];
    int an;
    int grupa;
    int n;
    int note[15];
    //int is;
}x,y;

void creare(char *nume)
{
    FILE *f=fopen(nume,"wb");
    while(!feof(stdin))
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
            //x.is=1;
            fwriteb(x,f);
            printf("Introduceti numarul matricol: ");
            scanf("%d",&x.nr);
        }
        printf("\n\n");
    }
    fclose(f);
}
void sortare_an(char* nume)
{
    FILE *f=fopen(nume,"r+b");
    fseek(f,0,SEEK_END);
    int n=ftell(f)/sizeof(struct STUDENT),i,j;
    for(i=0;i<n-1;i++)
    {
        fseek(f,i*sizeof(struct STUDENT),0);
        fread(&x,sizeof(struct STUDENT),1,f);
        for(j=i+1;j<n;j++)
        {
            freadb(y,f);
            if(x.an>y.an)
            {
                fseek(f,i*sizeof(struct STUDENT),0);
                fwriteb(y,f);
                fseek(f,j*sizeof(struct STUDENT),0);
                fwriteb(x,f);
                x=y;
            }
        }
    }
    fclose(f);
}
void sortare_grupa(char* nume)
{
    FILE *f=fopen(nume,"r+b");
    fseek(f,0,SEEK_END);
    int n=ftell(f)/sizeof(struct STUDENT),i,j;
    for(i=0;i<n-1;i++)
    {
        fseek(f,i*sizeof(struct STUDENT),0);
        fread(&x,sizeof(struct STUDENT),1,f);
        for(j=i+1;j<n;j++)
        {
            freadb(y,f);
            if(x.an==y.an)
                if(x.grupa>y.grupa)
                {
                    fseek(f,i*sizeof(struct STUDENT),0);
                    fwriteb(y,f);
                    fseek(f,j*sizeof(struct STUDENT),0);
                    fwriteb(x,f);
                    x=y;
                }
        }
    }
    fseek(f,i*sizeof(struct STUDENT),0);
    freadb(x,f);
    fwriteb(x,f);
    fclose(f);
}
void afisare(char* nume)
{
    FILE *f=fopen(nume,"rb");
    int i;
    printf("Nr.\tNume  \tAn\tGrupa\tNote\n");
    while(!feof(f))
    {
        fread(&x,sizeof(struct STUDENT),1,f);
        printf("%d\t",x.nr);
        for(i=0;i<30;i++)
            if(x.nume[i]==10)
            {
                x.nume[i]='\0';
            }
        printf("%s\t",x.nume);
        printf("%d\t",x.an);
        printf("%d\t",x.grupa);
        for(i=0;i<x.n;i++)
            printf("%d ",x.note[i]);
        printf("\n");
    }
}
float medie(struct STUDENT x)
{
    int i;
    float s=0;
    for(i=0;i<x.n;i++)
        s+=x.note[i];
    return s/x.n;
        
}
void listare()
{
    int i,grupa,j=0,k,v;
    float medie1=0,medie2=0;
    FILE *f=fopen(fisierbinar,"rb"),*g=fopen(fisiertext,"w");;
    freadb(x,f);
    for(i=1;i<=3;i++)
    {
        fprintf(g,"Anul %d\n",i);
        while(x.an<i+1 && !feof(f))
        {
            grupa=x.grupa;
            fprintf(g,"\tGrupa %d\n",x.grupa);
            k=0;
            medie1=0;
            while(x.grupa==grupa && !feof(f))
            {
                for(v=0;v<30;v++)
                    if(x.nume[v]==10)
                    {
                        x.nume[v]='\0';
                    }
                fprintf(g,"\t%d.\t%s\t%.1f\n",++k,x.nume,medie(x));
                medie1+=medie(x);
                freadb(x,f);
            }
            j++;
            fprintf(g,"Media grupei %d\t%.1f\n",grupa,medie1/k);
            medie2+=(medie1/k);
        }
        fprintf(g,"Media anului %d\t%.1f\n",i,medie2/j);
        j=0;
        medie2=0;
    }
    fclose(f);
    fclose(g);
}
int main(void)
{
    //creare(fisierbinar);
    //sortare_an(fisierbinar);
    sortare_grupa(fisierbinar);
    afisare(fisierbinar);
    listare();
}
