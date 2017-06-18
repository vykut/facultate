//
//  index.h
//  seminar11
//
//  Created by Victor Socaciu on 10/05/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#ifndef index_h
#define index_h


#include<string.h>
#include "tipuri.h"

//vezi Anexa 1

TARTICOL x;

char nume[20], numed[20], numei[20];

TFISIER f;

TFISIER ind;

// Extindere nume prin adaugarea extensiilor

void Extinde()

{ strcpy(numei,nume);
    
    strcat(numei,".idx");
    
    strcpy(numed,nume);
    
    strcat(numed,".dat");
    
}

void Open_index()

{ f=fopen(numed,"rb+");
    
    ind=fopen(numei,"rb+");
    
}
// Sortarea tabelei index si eliminarea inregistrarilor sterse

// I -

// E -

void Sort()

{ TART_INDEX a,b;
    
    TFISIER ind1;
    
    long i,j;
    
    //copierea tabelei index intr-un fisier temporar (numai art. valide)
    
    ind1=fopen("temp.idx","wb+");
    
    rewind(ind);
    
    fread(&a,sizeof(a),1,ind);
    
    while(!feof(ind))
        
    { if(a.is) fwrite(&a,sizeof(a),1,ind1);
        
        fread(&a,sizeof(a),1,ind);
        
    }
    
    fclose(ind);
    
    //sortarea fisierului temporar
    
    fseek(ind1,0,SEEK_END);
    
    long n=ftell(ind1)/sizeof(a);
    
    for(i=0;i<n-1;i++)
        
    { fseek(ind1,i*sizeof(a),SEEK_SET);
        
        fread(&a,sizeof(a),1,ind1);
        
        for(j=i+1;j<n;j++)
            
        { fseek(ind1,j*sizeof(a),SEEK_SET);
            
            fread(&b,sizeof(a),1,ind1);
            
            if (strcmp(a.cheie,b.cheie)>0)
                
            { fseek(ind1,i*sizeof(a),SEEK_SET);
                
                fwrite(&b,sizeof(a),1,ind1);
                
                fseek(ind1,j*sizeof(a),SEEK_SET);
                
                fwrite(&a,sizeof(a),1,ind1);
                
            }
            
        }
        
    }
    
    fclose(ind1);
    
    //inlocuirea tabelei index cu fisierul sortat
    
    remove(numei);
    
    rename("temp.idx",numei);
    
    ind=fopen(numei,"rb+");
    
}

/* Cautarea articolului cu cheia Key si plasarea pointerului de fisier in tabela de indexuri pe articolul respectiv*/

// I - cheia cautata

// E - cod succes: 1 - a fost gasit articolul; 0 - nu a fost gasit articolul

int SeekKey(char *Key)

{ long ls=0, ld, m, n;
    
    TART_INDEX a;
    
    int gasit=0;
    
    //rewind(ind);
    fseek(ind,0,SEEK_END);
    
    n=ftell(ind)/sizeof(TART_INDEX);
    
    ld=n-1;
    
    while((ls<=ld)&&(!gasit))
        
    { m=(ls+ld)/2;
        
        fseek(ind,m*sizeof(a),SEEK_SET);
        
        fread(&a,sizeof(a),1,ind);
        
        if (strcmp(a.cheie,Key)==0)
            
            gasit=1;
        
        else
            
            if (strcmp(a.cheie,Key)>0)
                
                ld=m-1;
        
            else
                
                ls=m+1;
        
    }
    
    if (gasit)
        
        fseek(ind,m*sizeof(a),SEEK_SET);
    
    return gasit;
    
}

// Crearea unui fisier indexat nou

// I -

// E -

void New_index()

{ f=fopen(numed,"wb+");
    
    ind=fopen(numei,"wb+");
    
}

// Deschiderea unui fisier indexat existent

// I -

// E -



// Inchiderea tabelei index

// I -

// E -

void Close_index()

{ fclose(ind);
    
    fclose(f);
    
}

// Citirea urmatorului articol in acces secvential

// I - adresa unde se depune articolul citit

// E - cod de succes: 1 - a fost citit; 0 - nu a fost gasit nici un articol

int ReadSec(TARTICOL *a)

{ TART_INDEX a1;
    
    int r;
    
    fread(&a1,sizeof(a1),1,ind);
    
    if(feof(ind))
        
        r=0;
    
    else
        
    { fseek(f,a1.nr_rel*sizeof(*a),SEEK_SET);
        
        fread(a,sizeof(*a),1,f);
        
        r=1;
        
    }
    
    return r;
    
}

// Citirea articolului cu o cheie data, in acces direct

// I - adresa unde se depune articolul citit, cheia articolului cautat

// E - cod de succes: 1 - a fost citit; 0 - nu a fost gasit nici un articol

int ReadKey(TARTICOL *a,char *Key)

{ TART_INDEX a1;
    
    int r;
    
    if (SeekKey(Key))
        
    { fread(&a1,sizeof(a1),1,ind);
        
        fseek(f,a1.nr_rel*sizeof(*a),SEEK_SET);
        
        fread(a,sizeof(*a),1,f);
        
        r=1;
        
    }
    
    else
        
        r=0;
    
    return r;
    
}

// Scrierea unui articol in acces secvential

// I - articolul care trebuie scris

// E - cod de succes: 1 - a fost scris; 0 - nu a fost scris articolul

int WriteSec(TARTICOL a)

{ TART_INDEX a1, ai;
    
    long n, n1;
    
    int r,r1;
    
    r=0;
    
    fseek(ind,0,SEEK_END);
    
    n=ftell(ind)/sizeof(a1);
    
    if(n>0)
        
    { fseek(ind,(n-1)*sizeof(a1),SEEK_SET);
        
        fread(&a1,sizeof(a1),1,ind);
        
        if (strcmp(a1.cheie,a.cheie)>=0) r1=0;
        
        else r1=1;
        
    }
    
    if((n==0) || (r1==1))
        
    { ai.is=1;
        
        strcpy(ai.cheie,a.cheie);
        
        fseek(f,0,SEEK_END);
        
        n1=ftell(f)/sizeof(a);
        
        ai.nr_rel=n1;
        
        fseek(ind,0,SEEK_END);
        
        fwrite(&ai,sizeof(ai),1,ind);
        
        fwrite(&a,sizeof(a),1,f);
        
        r=1;
        
    }
    
    return r;
    
}

//scrierea unui articol in acces direct

// I - fisierul de date, articolul care trebuie scris (contine cheia)

// E - cod de succes: 1 - a fost scris; 0 - nu a fost scris articolul

int WriteKey(TARTICOL a)

{ char Key[7];
    
    TART_INDEX a1;
    
    long n;
    
    int r;
    
    strcpy(Key,a.cheie);
    
    if(SeekKey(Key))
        
        r=0;
    
    else
        
    { a1.is=1;
        
        strcpy(a1.cheie,a.cheie);
        
        fseek(f,0,SEEK_END);
        
        n=ftell(f)/sizeof(a);
        
        a1.nr_rel=n;
        
        fwrite(&a,sizeof(a),1,f);
        
        fseek(ind,0,SEEK_END);
        
        fwrite(&a1,sizeof(a1),1,ind);
        
        Sort();
        
        r=1;
        
    }
    
    return r;
    
}

// Stergerea urmatorului articol, in acces secvential

// I -

// E - cod de succes: 1 - a fost sters; 0 - nu a fost sters articolul

int DeleteSec()

{ TART_INDEX a1;
    
    int r;
    
    long pos=ftell(ind);
    
    fread(&a1,sizeof(a1),1,ind);
    
    if(feof(ind))
        
        r=0;
    
    else
        
    { fseek(ind,pos,SEEK_SET);
        
        a1.is=0;
        
        fwrite(&a1,sizeof(a1),1,ind);
        
        Sort();
        
        r=1;
        
    }
    
    return r;
    
}

// Stergerea articolului cu o anumita cheie, in acces direct

// I - cheia articolului care trebuie sters

// E - cod de succes: 1 - a fost scris; 0 - nu a fost scris articolul

int DeleteKey(char *Key)

{ int r;
    
    if (SeekKey(Key))
        
        r=DeleteSec();
    
    else
        
        r=0;
    
    return r;
    
}

// Suprascrierea ultimului articol citit, cu scopul modificarii

// I - articolului care trebuie suprascris

// E - cod de succes: 1 - suprascrierea a reusit, 0 - suprascrierea a esuat

// esec daca ultima cheie citita difera de a noului articol

int RewriteKey(TARTICOL a)

{ int r;
    
    long p;
    
    TART_INDEX ai;
    
    r=0;
    
    p=ftell(ind)/sizeof(TART_INDEX);
    
    if(p>0)
        
    { fseek(ind,(p-1)*sizeof(TART_INDEX),0);
        
        fread(&ai,sizeof(TART_INDEX),1,ind);
        
        if (strcmp(ai.cheie,a.cheie)==0) r=1;
        
    }
    
    if(r)
        
    { fseek(f,ai.nr_rel*sizeof(TARTICOL),0);
        
        fwrite(&a,sizeof(TARTICOL),1,f);
        
    }
    
    return r;
    
}

#endif /* index_h */
