#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "network.h"
#include "relink.h"
#include "conex_swap.h"

//Crea el anillo de longitud l con k vecinos y asigno el estado de los individuos.

int condicion_inic_t(int *ani, int *vec, int l, int k, float rho, float p, int n_ref) {
  int i, j, t;
  int *index_pac;

  index_pac = malloc(l*sizeof(int));

  //Asigno el valor según su posición a todos los elementos de la red.
  for (i=k; i<l+k;i++) {
      *(ani+i) = 0; //Estado susceptible (0) para todos los individuos.
  }

  //Creo el vector de indeces para los pacientes a inmunizar.
  for (i=0; i<l; i++) {
    *(index_pac + i) = i; //Asigno cada valor según su índice.
  }

  //Arma la matriz de contactos.
  network(ani,vec,l,k);

  //Redireccionamiento de la mitad (derecha) de los contactos.
  relink(ani,vec,l,k,p);

  //Ordena los indices de los pacientes de mayor a menor según sus contactos.
  conex_swap(index_pac,vec,l,k);

  //Asigno los individuos inmunizados de forma selectiva.
  t = 0;
  while (n_ref < rho*l) {
    *(ani+ (*(index_pac + t)+k)) = 1;
    t = t + 1;
    n_ref = n_ref + 1;
  }

  //Asigno el individuo infectado.
  j = k+(rand()%l);
  *(ani+j) = -1; //Tomo un individuo j al azar y lo infecto.

  //Creo la periodicidad.
  for (i=0;i<k;i++) {
    *(ani+i) = *(ani+l+i); //Toma los valores del final.
    *(ani+l+k+i) = *(ani+k+i); //Toma los valores del principio.
  }

  printf("El paciente infectado es el %d.\n", j-1);

  free(index_pac);

  return j;
}
