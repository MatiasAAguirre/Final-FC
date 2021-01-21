#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Relinkea los k vecinos de la derecha.

int relink(int *ani,int *vec, int l, int Ka, float p) {
  int *redi;
  int i, j, k;
  float r;

  redi = malloc((l-2*Ka-1)*sizeof(int)); //El tamaño es el del anillo menos los posibles vecinos 2*Ka (izquierda y derecha) menos el elemento que miro.

  for (i=Ka; i<l+Ka; i++) {

    //Posibles vecinos, si solo hay opciones a la derecha de i+Ka.
    if (i-2*Ka<=0 && l-i-1>0) {
      for (j=0; j<l-2*Ka-1; j++) {
        *(redi+j) = i+Ka+j;
      }
    }

    //Posibles vecinos, si hay opciones tanto a la izquierda como a la derecha de i-+Ka.
    if (i-2*Ka>0 && l-i-1>0) {
      for (j=0; j<i-2*Ka; j++) {
        *(redi+j) = Ka+j-1;
      }
      for (j=i-2*Ka; j<l-2*Ka-1; j++) {
        *(redi+j) = 3*Ka+j;
      }
    }

    //Posibles vecinos, si solo hay opciones a la izquierda de i-Ka.
    if (i-2*Ka>0 && l-i-1<=0) {
      for (j=0; j<l-2*Ka-1; j++) {
        *(redi+j) = i-l+Ka+j;
      }
    }

    //Redirecciono solo los vecinos de la derecha utilizando redi.
    for (j=Ka+1;j<2*Ka+1;j++) {
      k=0;
      r = ((float)rand())/((float) RAND_MAX); //r para ver si j cambia o no.
      if (r<=p) {
        /*r = ((float)rand())/((float) RAND_MAX); //r para ver por cual cambia. No puedo usar el anterior r porque pertenece al intervalo [0,p), necesito que pertencezca al [0,1].
        while (r>(k+1)/((float)(l-2*Ka-1))) {
          k=k+1;
        }*/
        k = (rand()%(l-2*Ka-1));
        *(vec+(i-Ka)*2*Ka+j-1) = *(redi+k); //Tomo el k de redi como nuevo vecino.
      }
    }
  }

  free(redi);

  return 0;
}
