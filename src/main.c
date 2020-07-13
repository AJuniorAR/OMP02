#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "fisi_vector.h"

#define N 8
#define SEMILLA 1000
#define VECES 100

int n[N] = {
    1000, 10000, 50000,
    100000, 200000, 500000,
    750000, 1000000};
//int a[N];  //de esta manera 1

double dursec[N], durpar[N];


int main(int argc, char **argv)
{
    //o de esta manera
    int dim;
    printf("%s,%s,%s,%s\n","nro","N","dursec","durpar");
    for (dim = 0; dim < N; dim++)
    {

        int *a;
        int veces;
        long suma, sumapar, suma1, suma2;
        double inicio, duracion;

        //inicializa
        srand(SEMILLA);
        a = (int *)calloc(n[dim], sizeof(int));
        aleatorio(0, n[dim], a);

        // Suma secuencial
        duracion = 0.0;
        for (veces = 0; veces < VECES; veces++)
        {

            inicio = omp_get_wtime();
            suma = suma_prefijo(0, n[dim], a);
            duracion += (omp_get_wtime() - inicio);
        }
        dursec[dim] = duracion / VECES;
        //---------------------------------------

        //Suma paralela
        duracion = 0.0;
        for (veces = 0; veces < VECES; veces++)
        {

            inicio = omp_get_wtime();

#pragma omp parallel sections
            {
                suma1 = suma_prefijo(0, n[dim] / 2, a);
#pragma omp section
                {
                    suma2 = suma_prefijo(n[dim] / 2, n[dim], a);
                }
            }
            sumapar = suma1 + suma2;
            duracion += (omp_get_wtime() - inicio);
        }
        durpar[dim] = duracion / VECES;
        
        printf("%i,%i,%f,%f\n",dim,n[dim],dursec[dim],durpar[dim]);
        free(a);
    }
    
    return 0;
}
