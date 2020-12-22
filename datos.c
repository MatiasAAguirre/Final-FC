#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "Final_FC2.c"

//Calculo los promedios de N=10000 con K=2 para 10000 pasadas por cada uno de los pares (rho,p).

int main(int argc, char const *argv[]) {
  int i, j, k, r;
  float p;
  float *rho;
  char *fps;
  FILE *fp;

  rho = malloc(5*sizeof(float));
  fps = malloc(5*sizeof("./Datos/Nr(p)_rho_0.4.out"));

  for (i=0; i<5; i++) {
    *(rho+i) = ((float)i/10);
  }

  for (i=0; i<5; i++) { //Uno por cada rho.
    sprintf(fps, "./Datos/Nr(p)_rho_0.%d.out", i);
    fp = fopen(fps, "w");

    for (j=0; j<21; j++) { //Uno por cada p.
      r = 0;
      p = 0.01+j*0.0495;
      for (k=0; k<1000; k++) { //Promedio entre 10000 corridas.
        r = r + Final_FC2(10000,2,p,*(rho+i));
        //printf("%d\n", r);
        printf("k=%d de j=%d de i=%d.\r", k, j, i);
      }
      fprintf(fp, "%f %f\n", p, ((float)r/((1-*(rho+i))*10000*1000)));
    }
    fclose(fp);
  }

  free(rho);

  return 0;
}
