//
//  main.c
//  salut
//
//  Created by Victor Socaciu on 04/04/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct STUDENT
{
    int nrMat;
    char nume[30];
    int an;
    int grupa;
    int n;
    int note[15];
} x;


// CITIRE DIN FISIER


/*int main(void)
 {
 FILE *f=fopen("fisier","r");
 int n,i;
 float *v,s=0;
 fscanf(f,"%d",&n);
 v=(float*)malloc(sizeof(float));
 for(i=0;i<n;i++)
 fscanf(f,"%f",&v[i]);
 for(i=0;i<n;i++)
 s+=v[i];
 printf("%.1f\n",s/n);
 return 0;
 }
 */


//CREARE FISIER CU DATE STUDENTI
int main(void)
 {
 FILE *f=fopen("fisier.out","wb");
 int i;
 printf("Introduceti numarul matricol: ");
 scanf("%d",&x.nrMat);
 while(!feof(stdin))
 {
 fflush(stdin);
 printf("Introduceti numele: ");
     fputs(x.nume,f);
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
 scanf("%d",&x.nrMat);
 }
 fclose(f);
 return 0;
 }



//MEDIA NOTELOR DUPA NR MATRICOL
/*int main(void)
{
    FILE *f=fopen("fisier.out","rb");
    float s;
    int nrMat,i;
    while(!feof(stdin))
    {
        printf("Introduceti numarul matricol: ");
        scanf("%d",&nrMat);
        while(!feof(f))
        {
            fread(&x, sizeof(struct STUDENT), 1, f);
            if(x.nrMat==nrMat)
            {
                s=0;
                for(i=0;i<x.n;i++)
                    s=s+x.note[i];
                printf("%.1f\n",s/x.n);
            }
        }
        rewind(f);
    }
    fclose(f);
}
*/



















