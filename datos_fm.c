#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "Random_inmu_fm2.c"

//Calculo los promedios de N=10000 con K=2 para 10000 pasadas por cada uno de los pares (rho,p).

int main(int argc, char const *argv[]) {
  int i, j, k, r;
  float p, rho;
  float *gamma_i, *gamma_c;
  char *fps;
  FILE *fp;

  fps = malloc(16*sizeof("./Datos_fm/Nr(p)_gamma_1.00.out"));
  gamma_i = malloc(10*sizeof(float));
  gamma_c = malloc(16*sizeof(float));

  for (i=0; i<10; i++) {
    *(gamma_i+i) = ((float)i/15);
  }

  for (i=0; i<16; i++) {
    *(gamma_c+i) = ((float)i/15);
  }

  p = 1.0;
  rho = 0.0;

  for (i=0; i<10; i++) { //Uno por cada gamma_i.
    sprintf(fps, "./Datos_fm/Nr(p)_gamma_%0.2f.out", *(gamma_i+i));
    fp = fopen(fps, "w");

    for (j=0; j<16; j++) { //Uno por cada gamma_c.

      r = 0;

      for (k=0; k<10000; k++) { //Promedio entre 10000 corridas.
        r = r + Random_inmu_fm2(5000,2,p,rho,*(gamma_i+i),*(gamma_c+j));
        //printf("%d\n", r);
        printf("k=%d de j=%d de i=%d.\r", k, j, i);
      }
      fprintf(fp, "%0.2f %f\n", *(gamma_c+j), ((float)r/((1-rho)*10000*5000)));
    }
    fclose(fp);
  }

  free(gamma_i);
  free(gamma_c);
  free(fps);

  return 0;
}
