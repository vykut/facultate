//
//  tipuri.h
//  seminar11
//
//  Created by Victor Socaciu on 10/05/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#ifndef tipuri_h
#define tipuri_h

//tipul fisier

#define TFISIER FILE*

//tipul cheii

typedef char TCHEIE[11];

//tipul articol din tabela index

typedef struct{ char is;
    
    TCHEIE cheie;
    
    long nr_rel;
    
} TART_INDEX;

//tipul articol din fisierul de date

typedef struct{ TCHEIE cheie;
    
    char numestud[35];
    
    int grupa;
    
    int an;
    
    int nr;
    
    int note[20];
    
} TARTICOL;

#endif /* tipuri_h */
