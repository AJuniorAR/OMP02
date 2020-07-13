#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "fisi_vector.h"

#define N 1000000
#define S 1000
#define V 100



long suma_prefijo(int ini ,int fin,int v[]){
    long s=0;
    for (int i = ini; i < fin ; i++)
    {
        s+= v[i];
    }
    
    return s;
}
int a[N];

//de esta manera 
//manera 1


int main(int argc,char **argv ){
    //o de esta manera
   // int *a;
   // a=(int *)calloc(N,sizeof(int))
   int veces;
    long suma,sumapar,suma1,suma2;
    double inicio,duracion,dursec,durpar;

    //inicializa
    srand(S);
    aleatorio(0,N,a);

    // Suma secuencial
     duracion=0.0;
    for (veces=0 ; veces<V ; veces++)
    {   
       
        inicio = omp_get_wtime();
        suma=suma_prefijo(0,N,a);
        duracion += (omp_get_wtime()-inicio);

    }
    dursec = duracion/V;
    printf("Suma=%li Tiempo Secuencial %f\n",suma,dursec);

    duracion=0.0;
   for (veces=0 ; veces<V ; veces++)
    { 
        
        inicio = omp_get_wtime();

    #pragma omp parallel sections 
    {   
        suma1=suma_prefijo(0,N/2,a);
        #pragma omp section
        {
             suma2=suma_prefijo(N/2,N,a);
        }
        
        
    }
    sumapar=suma1+suma2;
    duracion += (omp_get_wtime()-inicio);
    }
    durpar = duracion/V;
    printf("Suma=%li Tiempo Paralelo %f",sumapar,durpar);

   // free(a)
    return 0;
}



