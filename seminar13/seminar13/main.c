//
//  main.c
//  seminar13
//
//  Created by Victor Socaciu on 24/05/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct {int vi, vf;
    
} muchie;

//- se preiau datele unui graf in forma tabelara din fisierul “nume” si se obtine o matrice de adiacenta si tabelul cu muchii care va contine o coloana suplimentara in care va fi memorata, pentru fiecare muchie componenta conexa din care face parte. Componenetele conexe sunt identificate prin indici incepand cu 1

//- in fisierul text suntdate: numarul de varfuri (n), numarul de muchii (m) si perechile de muchii, varfurile sunt 1,2,...,n, muchiile sunt de forma (i,j), cu i<j

void preia_graf (char *nume, int a[][100], int *n, int T[][3], int *m)

{
    int i, j, u, v;
    
    //-declarare variabile intregi: i,j,u,v;
    
    //- declarare variabila de tip
    FILE *f;
    
    //- se deschide fisierul:
    f=fopen(nume, "r");
    
    //-se verifica deschiderea fisierului:
    
    if (!f) printf("Fisierul NU s-a deschis\n");
    
    else  printf("Fisierul s-a deschis\n");
    
    //- citire nr de vf si de muchii din fisier si afisare pe ecran:
    
    fscanf(f,"%d %d", n, m);
    
    printf("%d %d\n", *n, *m);
    
    //- initializare matrice de adiacenta:
    
    for(i=0;i<*n;i++)
        
        for(j=0;j<*n;j++)
            
            a[i][j]=0;
    
    //- construire forma tabelara si marcarea drumurilor in matricea de adiacenta
    
    for(i=0;i<*m;i++)
        
    { fscanf(f,"%d %d", &u, &v);
        
        printf("%d %d\n", u, v);
        
        T[i][0]=u;
        
        T[i][1]=v;
        
        a[u-1][v-1]=a[v-1][u-1]=1;
        
    }
    
    //- se inchide fisierul:
    fclose(f);
    
}

//- functie pentru calculul matricei existentei drumurilor ROY-WARSHALL

void RoyW (int **a, int n, int **m)

{ //- declarare variabile intregi:
    int i,j,k;
    
    //- initializare matrice m cu matricea de adiacenta
    m=a;
    //- verificare drumuri intre varfuri. Daca taote elementele sunt 1 pentru m[][] atunci graful este conex.
    
    for(i=0;i<n;i++)
        
        for(j=0;j<n;j++)
            
            if (m[i][j]==0)
                
                for(k=0;k<n;k++)
                    
                    if(m[i][k]&&m[k][j])
                        
                        m[i][j]=1;
    
}

//- functie pentru construirea componentei conexe care contine varful i pe baza matricei existentei drumurilor si a reprezentarii tabelare

//fie p eticheta asociata componentei conexe care contine varful i

//multimii farfurilor ii este asociat un vector c: - c[v]=0 daca v+1 nu a fost considerat pentru nicio componenta conexa;

// - c[v]=r, r nenul daca v este in componenta conexa etichetata cu r;

//determinarea varfurilor componentei conexe: este parcursa lini i-1 din m si, pentru toate varfurile k+1 neconsiderate anterior (c[k]=0) cu M[i-1][k]=1, c[k]=p

//determinarea multimii muchiilor componentei conexe p: este parcursa tabela T si, daca primul varf al muchiei k, T[k][0], este varf din componenta conexa p (c[T[k][0]-1]=p), atunci T[k][2]=p - muchia este in componenta conexa p

void comp_conexa(int M[][100], int n, int *c, int i, int p, int T[][3], int m)

{
    int k;
    //- declarare variabile intregi: k;
    
    //- algoritmul descris mai sus:
    
    c[i-1]=p;
    
    for(k=0;k<n;k++)
        
        if((M[i-1][k])&&(c[k]==0))
            
            c[k]=p;
    
    for(k=0;k<m;k++)
        
        if (c[T[k][0]-1]==p)
            
            T[k][2]=p;
    
}

//- functie pentru calculul tuturor componentelor conexe; ncc - nr componente conexe

void componente_conexe(int M[][100], int n, int *c, int T[][3], int m, int *ncc)

{ int i,gata,p,v,j;
    
    // - declarare variabile intregi: i, gata, p, v, j, ;
    
    // - initializara vector componente conexe, “gata”, varf curent (v), eticheta componenta conexa (p) :
    
    c=(int*)calloc(n,sizeof(int));
    
    gata=0;
    
    v=1;
    
    p=1;
    
    // - algoritm de calcul pentru toate componentele conexe
    
    while(!gata)
        
    { comp_conexa(M,n,c,v,p,T,m);
        
        for(j=0;(j<n)&&c[j];j++);
        
        if (j==n) gata=1;
        
        else { v=j+1;
            
            p++;
            
        }
        
    }
    
    *ncc=p;
    
}

//- in functia main:
int main(void)
{
    
    //- declarare variabile intregi:
    int a[100][100], **M, n, c[100], T[1000][3], p, m, i,j,k,v,nc,nrv;
    
    //- apelare functie de preluare graf din fisier:
    
    preia_graf("grafDij.txt", a, &n, T, &m);
    
    //- apelare functie pentru construire matrice drumuri:
    
    RoyW(a,n,M);
    
    // - afisarea matricei de existenta a drumurilor:
    
    printf("matricea existentei drumurilor este:\n");
    
    for(i=0;i<n;i++)
        
    { for(j=0;j<n;j++)
        
        printf("%d\t", M[i][j]);
        
        printf("\n");
        
    }
    
    //  - determinarea tuturor componentelor conexe ale grafului. Daca nc (nr componente) este 1 atunci graful este conex si se afiseaza informatiile despre el. Altfel pentru fiecare componenta identificata se afiseaza elementele
    
    printf("\nComponentele conexe ale grafului sunt\n");
    
    componente_conexe(M,n,c,T,m,&nc);
    
    if (nc==1)
        
    {
        
        printf("Graful este conex!");
        
        printf("\n Varfurile:");
        
        for(i=0;i<n;i++)
            
            printf("%d\t", i+1);
        
        printf("\nMuchiile");
        
        for(i=0;i<m;i++)
            
            printf("(%d,%d)\t", T[i][0], T[i][1]);
        
        printf("\n");
        
    }
    
    //altfel pentru fiecare componenta identificata se afiseaza elementele
    
    else
        
        for (k=1;k<=nc;k++)
            
        { printf ("\nComponenta conexa %d", k);
            
            printf("\nVarfuri: ");
            
            nrv=0;
            
            for(i=0;i<n;i++)
                
                if(c[i]==k)
                    
                { printf("%d\t", i+1); //afisare elemente pentru componenta conexa k
                    
                    nrv++;
                    
                }
            
            if (nrv==1)
                
                printf ("\n Varf izolat");
            
            else
                
            { printf("\nMuchii: ");
                
                for(i=0;i<m;i++)
                    
                    if (T[i][2]==k)
                        
                        printf ("(%d,%d)\t", T[i][0],T[i][1]);
                
                printf("\n");
                
            }
            
        }
    
}
