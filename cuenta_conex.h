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

 int ver_repe(int *vec, int l, int Ka) {
   int i, j, k, c;

   for (i=0;i<l;i++) {
     c = 0;
     for (j=0;j<2*Ka;j++) {
       printf("%d ", *(vec+i*2*Ka+j));
       for (k=0; k<j; k++) {
         if (*(vec+i*2*Ka+j)==*(vec+i*2*Ka+k)) {
           c++;
         }
       }
     }
     printf("\n");
     if (c!=0) {
         printf("Hay %d repeticiones para la fila %d.\n", c, i);
     }
     printf("\n");
   }

   return 0;
 }
