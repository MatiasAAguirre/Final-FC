#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "Targeted_inmu2.c"

//Calculo los promedios de N=10000 con K=2 para 10000 pasadas por cada uno de los pares (rho,p).

int main(int argc, char const *argv[]) {
  int i, j, r;
  float p;
  float *rho;
  char *fps;
  FILE *fp;

  rho = malloc(13*sizeof(float));
  fps = malloc(1*sizeof("./Datos_t/Nr(p)_rho_0.4.out"));

  for (i=0; i<13; i++) {
    *(rho+i) = ((float)i/30);
  }

  sprintf(fps, "./Datos_t/Nr(p)_rho_max.out");
  fp = fopen(fps, "w");

  for (i=0; i<13; i++) { //Uno por cada rho.
    r = 0;
    p = 1;

    for (j=0; j<10000; j++) { //Promedio entre 10000 corridas.
      r = r + Targeted_inmu2(5000,2,p,*(rho+i));
      //printf("%d\n", r);
      printf("j=%d de i=%d.\r", j, i);
    }
    fprintf(fp, "%f %f\n", (*(rho+i)), ((float)r/((1-*(rho+i))*10000*5000)));
  }

  fclose(fp);

  free(rho);
  free(fps);

  return 0;
}
