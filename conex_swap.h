#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int swap (int *ani, int *conex, int l) { //Realiza los intercambios.
  int i, j, temp1, temp2;

  for (i=0; i<l; i++) {
    for (j=i+1; j<l; j++) {
      if (*(conex+i) < *(conex+j)) { //Compara valores.
        //Ordena las conexiones.
        temp1 = *(conex+i);
        *(conex+i) = *(conex+j);
        *(conex+j) = temp1;

        //Ordena los pacientes.
        temp2 = *(ani+i);
        *(ani+i) = *(ani+j);
        *(ani+j) = temp2;
      }
    }
  }

  return 0;
}

//Cuenta cuantas conexiones hay entre los pacientes y arregla la tira de pacientes
//de mayor a menor según sus conexiones.

int conex_swap(int *ani, int *vec, int l, int k) {
  int i, j;
  int *conex;

  conex = malloc(l*sizeof(int));

  for(i=0; i<l; i++) {
    *(conex + i) = 0;
  }

  for (i=0;i<l;i++) {
    for (j=0;j<2*k;j++) {
        *(conex + *(vec+i*2*k+j) - 1) = *(conex + *(vec+i*2*k+j) - 1) + 1;
    }
  }
  //imprimir_tira(conex,l);
  //imprimir_tira(ani,l);

  swap(ani,conex,l);

  free(conex);
  return 0;
}
