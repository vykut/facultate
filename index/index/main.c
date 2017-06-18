#include<stdio.h>

void creare(FILE *f)
{
    int x;
    float y;
    f=fopen("matrice.dat","wb");
    scanf("%d",&x);
    fwrite(&x,sizeof(int),1,f);
    scanf("%f",&y);
    while(!feof(stdin))
    {
        fwrite(&y,sizeof(float),1,f);
        scanf("%f",&y);
    }
    fclose(f);
}



int main()
{
    FILE *f;
    creare(f);
    float max, element;
    int i,j,r,n;
    long m;
    f=fopen("matrice.dat","rb");
    fread(&n,sizeof(int),1,f);
    fseek(f,0,SEEK_END);
    m=(ftell(f)-sizeof(int))/((sizeof(float)*n));
    //printf("%lu",sizeof(int));
    for(j=0;j<n;j++)
    {
        fseek(f,j*sizeof(float)+sizeof(int),0);
        fread(&element,sizeof(float),1,f);
        max=element;
        for(i=0;i<m;i++)
        {
            r = i*n+j;
            fseek(f,r*sizeof(float)+sizeof(int),0);
            fread(&element,sizeof(float),1,f);
            max=(element>max)?element:max;
        }
        printf("Maximul pe coloana %d este %7.3f\n",j,max);
    }
    fclose(f);
}
