#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

#include "Random_inmu2.c"

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
      p = exp(-4.6+0.23*j);
      //p = 0.01+j*0.0495;
      for (k=0; k<10000; k++) { //Promedio entre 10000 corridas.
        r = r + Random_inmu2(5000,2,p,*(rho+i));
        //printf("%d\n", r);
        printf("k=%d de j=%d de i=%d.\r", k, j, i);
      }
      fprintf(fp, "%f %f\n", p, ((float)r/((1-*(rho+i))*10000*5000)));
    }
    fclose(fp);
  }

  free(rho);
  free(fps);

  return 0;
}
