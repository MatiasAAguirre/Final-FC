#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Crea el anillo de longitud l con k vecinos y asigno el estado de los individuos.

int condicion_inic(int *ani, int l, int k, float rho, int n_ref) {
  int i, j;
  float r;


  //Asigno el valor según su posición a todos los elementos de la red.
  for (i=k; i<l+k;i++) {
      *(ani+i) = 0; //Estado susceptible (0) para todos los individuos.
  }

  //Asigno los individuos inmunizados de forma aleatoria.
  for (i=k;i<l+k;i++) {
    r = ((float)rand())/((float) RAND_MAX); //r para ver si i cambia o no.
    if (r<=rho) {
      *(ani+i) = 1;
      n_ref = n_ref + 1;
    }
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

  return j;
}
