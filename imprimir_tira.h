#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Imprime la tira de longitud a.

int imprimir_tira(int *tira, int a) {
   int i;

   for (i=0;i<a;i++) {
       printf("%02d ", *(tira+i));
   }

   printf("\n");

   return 0;
 }
