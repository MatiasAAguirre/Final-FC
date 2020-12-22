#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Creo los vecinos de longitud 2*k.

int network(int *ani, int *vec, int l, int k) {
  int i, j;

  //Guardo la posición de los vecinos.
  for (i=k;i<l+k;i++) {
    for(j=1;j<k+1;j++) {
      *(vec+(i-k)*2*k+j-1) = i-k+j-1; //Los k vecinos de la izquierda.
    }
    for (j=k+1;j<2*k+1;j++) {
      *(vec+(i-k)*2*k+j-1) = i-k+j; //Los k vecinos de la derecha.
    }
  }

  //---------------------------------------------------------------------
  //Lo que está a partir de ahora evita que k!=2, OJO! (Modificación a futuro (si es necesario), hacerlo general.)
  for (i=0;i<k;i++) { //Para el primer paciente y el último, respectivamente.
    *(vec+i) = l+i; //Toma los valores del final.
    *(vec+(l-1)*2*k+2+i) = k+i; //Toma los valores del principio.
  }
  *(vec+2*k) = l+1; //Toma el valor correcto del primer vecino del segundo paciente.
  *(vec+(l-2)*2*k+3) = k+1; //Toma el valor correcto del último vecino del antúltimo paciente.
  //---------------------------------------------------------------------

  return 0;
}
