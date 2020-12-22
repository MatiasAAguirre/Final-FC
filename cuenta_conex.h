#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Cuenta en la matriz fxc la cantidad de vínculos.

int imprimir_matriz(int *matriz, int f, int c) {
   int i,j;

   for (i=0;i<f;i++) {
     for (j=0;j<c;j++) {
       printf("%02d ", *(matriz+i*c+j));
     }
     printf("\n");
   }

   printf("\n");

   return 0;
 }
