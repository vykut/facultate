//
//  main.c
//  tema_2_1_8
//
//  Created by Victor Socaciu on 03/06/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rand 200


int main(void)
{
    FILE *f=fopen("tema8.txt","w+"),*g=fopen("tema8.csv","r");
    char s[200];
    int nr=0,nr_cuv,nr_cuv2=0,nr_rand,rand_lung=0,cuv_scurt=200,cuv_lung=0,i,indice;
    while(!feof(g))
    {
        nr_cuv=0;
        indice=0;
        fgets(s,rand,g);
        nr++;
        if(strlen(s)>rand_lung)
            rand_lung=strlen(s);
        for(i=0;i<rand;i++)
            if(s[i]==',')
            {
                nr_cuv++;
                if(i-indice>cuv_lung)
                    cuv_lung=i-indice-1;
                if(i-indice<cuv_scurt)
                    cuv_scurt=i-indice;
                indice=i;
            }
        if(nr_cuv>nr_cuv2) {
            nr_cuv2=nr_cuv;
            nr_rand=nr;
        }
    }
    fprintf(f,"Nr. randuri || Nr. maxim cuvinte || Nr. rand || Lungime maxima rand || cel mai mic cuvant || cel mai mare cuvant\n");
    fprintf(f,"%d %15d %19d %12d %21d %21d",nr-1,nr_cuv2+1,nr_rand,rand_lung-1,cuv_scurt,cuv_lung);
}
