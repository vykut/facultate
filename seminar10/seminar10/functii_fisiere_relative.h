//
//  functii_fisiere_relative.h
//  seminar10
//
//  Created by Victor Socaciu on 03/05/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#ifndef functii_fisiere_relative_h
#define functii_fisiere_relative_h

#include <stdio.h>

#include<stdlib.h>

#include<string.h>



// numar total spatii in fisier (nr. articole fizice)

// I - fisierul, dimensiunea unui articol logic

// E - nr. articole fizice (-1 daca fisierul nu e deschis)

int NrSpatii(FILE* f, long dim)

{ long p;
    
    int nr;
    
    nr=-1;
    
    if(f)
        
    { p=ftell(f);
        
        fseek(f,0,SEEK_END);
        
        nr=ftell(f)/(dim);
        
        fseek(f,p,SEEK_SET);
        
    }
    
    return nr;
    
}

// pozitia curenta in fisier

// I - fisierul, dimensiunea unui articol logic

// E - pozitia curenta, in nr. de articole, -1 daca fisierul e inchis

int Pozitia(FILE* f, long dim)

{ int nr;
    
    nr=-1;
    
    if(f)
        
        nr=ftell(f)/(dim);
    
    return nr;
    
}

// preformare fisier

// I - fisierul, dim. art., nr. art. pentru preformare/extindere

// E - cod eroare: 0 - succes, 1 - fisierul era inchis

int Preformare(FILE* f, long dim, int nr)

{ int i,er;
    
    char *art;
    
    er=1;
    
    if(f)
        
    { fseek(f,0,SEEK_END);
        
        art=(char*)malloc(dim);
        
        art[0]=0;
        
        for(i=0;i<nr;i++)
            
            fwrite(art,dim,1,f);
        
        er=0;
        
        free(art);
        
    }
    
    return er;
    
}

// pozitionare

// I - fisierul, dim. art., pozitia dorita in nr. relativ articol

// E - cod eroare, 0 - succes, 1 - pozitia prea mare, 2 - fis. inchis

int Pozitionare(FILE* f, long dim, int p)

{ int er;
    
    er=2;
    
    if(f)
        
        if(p<NrSpatii(f,dim))
            
        { fseek(f,p*(dim),SEEK_SET);
            
            er=0;
            
        }
    
        else
            
            er=1;
    
    return er;
    
}

// citire in acces secvential, urmatorul articol

// I - fisierul, dim. art., adresa la care se depune articolul citit

// E - cod eroare, 0 - art. citit, 1 - fis. inchis, 2 - sfirsit fisier

int CitesteUrmatorul(FILE* f, long dim, void* adresa)

{ char* art;
    
    int er=1;
    
    if(f)
        
    { art=(char*)malloc(dim);
        
        fread(art,dim,1,f);
        
        while((!feof(f)) && (er==1))
            
        { if(art[0]!=0)
            
        { er=0;
            
            memcpy(adresa,art+1,dim);
            
        }
            
        else
            
            fread(art,dim,1,f);
            
        }
        
        if(er==1) er=2;
        
        free(art);
        
    }
    
    return er;
    
}

// citire in acces direct

// I - fisierul, dim. art., cheia art., adresa unde se depune articolul

// E - cod eroare, 0 - art. citit, 1 - fis. inchis sau poz. prea mare,

// 2 - cheie invalida

int CitestePozitia(FILE* f, long dim, int poz, void* adresa)

{ char* art;
    
    int er;
    
    er=Pozitionare(f, dim, poz);
    
    if(!er)
        
    { art=(char*)malloc(dim);
        
        fread(art,dim,1,f);
        
        if(art[0]==0)
            
            er=2;
        
        else
            
        { er=0;
            
            memcpy(adresa, art+1, dim);
            
        }
        
        free(art);
        
    }
    
    return er;
    
}

// scriere articol in acces direct

// I - fisierul, dim. art., adresa articolului, cheia articolului

// E - cod eroare, 0 - succes, 1 - fis. inchis, 2 - cheie invalida

int ScriePozitia(FILE* f, long dim, void* adresa, int poz)

{ char* art;
    
    int n,er=1;
    
    if(f)
        
    { n=NrSpatii(f,dim);
        
        if(poz>=n)
            
            Preformare(f,dim,poz-n+1);
        
        art=(char*)malloc(dim);
        
        Pozitionare(f,dim,poz);
        
        fread(art,dim,1,f);
        
        if(art[0]==1)
            
            er=2;
        
        else
            
        { er=0;
            
            memcpy(art+1,adresa,dim);
            
            art[0]=1;
            
            Pozitionare(f,dim,poz);
            
            fwrite(art,dim,1,f);
            
        }
        
        free(art);
        
    }
    
    return er;
    
}

// suprascriere articol in vederea modificarii, in acces direct

// I - fisierul, dim. art., adresa articolului, cheia articolului

// E - cod eroare: 0 - succes, 1 - fis. inchis, 2 - pozitia e prea mare

int RescriePozitia(FILE* f, long dim, void* adresa, int poz)

{ char* art;
    
    int n,er=1;
    
    if(f)
        
    { n=NrSpatii(f,dim);
        
        if(poz>=n)
            
            er=2;
        
        else
            
        { art=(char*)malloc(dim);
            
            Pozitionare(f,dim,poz);
            
            er=0;
            
            memcpy(art+1,adresa,dim);
            
            fwrite(art,dim,1,f);
            
        }
        
        free(art);
        
    }
    
    return er;
    
}

// sterge articolul cu cheia data

// I - fisierul, dimensiunea unui articol, cheia articolului de sters

// E - cod eroare, 0 - succes, 1 - fis. inchis sau pozitie prea mare, 2 - cheie invalida (spatiu gol),

int Sterge(FILE*f, long dim, int poz)

{char* art;
    
    int er;
    
    er=Pozitionare(f,dim,poz);
    
    if(!er)
        
    { art=(char*)malloc(dim);
        
        fread(art,dim,1,f);
        
        if(art[0]==0)
            
            er=2;
        
        else
            
        { er=0;
            
            art[0]=0;
            
            Pozitionare(f,dim,poz);
            
            fwrite(art,dim,1,f);
            
        }
        
        free(art);
        
    }
    
    return er;
    
}

#endif /* functii_fisiere_relative_h */
