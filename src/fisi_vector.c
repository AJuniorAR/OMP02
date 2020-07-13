
#include <stdio.h>
#include "fisi_vector.h"

void ceros( int ini, int fin, int v[]) {
    for( int i=ini; i<fin; i++ ) {
        v[i] = 0;
    }
}

void aleatorio(int ini, int fin, int v[]) {
    for( int i=ini; i<fin; i++ ) {
        v[i] = rand();
    }

}

void sumar( int ini, int fin, int a[], int b[], int c[]) {
    for( int i=ini; i<fin; i++ ) {
       c[i] = a[i] + b[i];
    }
}
