//
//  main.c
//  tema_2_2_2
//
//  Created by Victor Socaciu on 04/06/2017.
//  Copyright © 2017 Victor Socaciu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void plata_unitate(int s, int* t, int n, int* sol)
{
    int i,sr;
    sr=s;
    for(i=0;i<n;i++)
    {
        sol[i]=sr/t[i];
        sr=sr%t[i];
    }
}

int main(void)
{
    FILE *f=fopen("greedy.dat","wb"),*g=fopen("verificare.txt","w");
    int s, n, *v, i, *sol;
    printf("Introduceti suma dorita: ");
    scanf("%d", &s);
    printf("Introduceti nr. de tipuri de bancnote: ");
    scanf("%d", &n);
    v = (int*)calloc(n,sizeof(int));
    sol = (int*)calloc(n,sizeof(int));
    for (i = 0; i < n; i++)
    {
        printf("Valoarea bancnotei %d: ", i + 1);
        scanf("%d", v + i);
    }
    plata_unitate(s,v,n,sol);
    fwrite(&sol,n*sizeof(int),1,f);
    fclose(f);
    f=fopen("greedy.dat","rb");
    fread(&sol,n*sizeof(int),1,f);
    for(i=0;i<n;i++)
        fprintf(g,"%d ",sol[i]);
    fclose(f);
    fclose(g);
    return 0;
}
