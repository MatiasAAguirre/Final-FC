#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "condicion_inic_t.h"
#include "imprimir_tira.h"
#include "imprimir_matriz.h"

int Targeted_inmu2(int l, int k, float p, float rho) {
  int *pac, *cont, *hist_t_inf;
  int i, Te, r, inf, cant_inf, t_inf, n_ref;
  float t;

  srand(time(NULL));
  pac = malloc((l+2*k)*sizeof(int));
  cont = malloc(l*2*k*sizeof(int));
  hist_t_inf = malloc(l*sizeof(int));

  t = 0; //Tiempo inicial.
  Te = 3; //Tiempo total de infección.
  for (i=0; i<l; i++) {
    *(hist_t_inf+i) = 0; //Todos tienen un tiempo 0 al incio que será reemplazado con el tiempo cuando fueron infectados.
  }
  n_ref = 0;

  if (2*k>=l) {
    printf("No es posible hacer con %d primeros contactos, alguno/s estará/n doblemente linkeado/s.\n", 2*k);
  } else {
    inf = condicion_inic_t(pac,cont,l,k,rho,p,n_ref); //Arma el vector pacientes y asigna sus estados. Devuelve la posición del paciente infectado 0.
    cant_inf = 1;//Cantidad de infectados al iniciar la simulación.

    //imprimir_tira(pac,(l+2*k));
    //printf("\n");
    //imprimir_matriz(cont,l,2*k);
    //printf("\n");
    /*ver_repe(cont,l,k);*/


//----------------------------------------------------------------------------------
    //Evolución de los contagios.
    while (cant_inf > 0) {
      //printf("Día %f\n", t);
      //printf("Miro el paciente infectado %d\n", inf);
      t_inf = *(hist_t_inf+inf-k); //Tomo el tiempo de infección del paciente inf.

      if (t-t_inf>Te) {
        *(pac+inf) = 1; //Cambia a estado refractario.
        //printf("Se curó el paciente %d\n", inf);
        for (i=0;i<k;i++) { //Mantiene la periodicidad.
          *(pac+i) = *(pac+l+i); //Toma los valores del final.
          *(pac+l+k+i) = *(pac+k+i); //Toma los valores del principio.
        }
        cant_inf = cant_inf - 1; //Elimina un infectado.
        //printf("Hay %d pacientes infectados.\n", cant_inf);
        n_ref = n_ref + 1;
      }
      else {
        r = (rand()%(2*k)); //Elijo un valor random entre [0,2*k].
        if (*(pac+(*(cont+(inf-k)*2*k+r)+1)) == 0) {
          *(pac+(*(cont+(inf-k)*2*k+r)+1)) = -1; //Contagio de algún contacto del paciente inf.
          //printf("Infecto a %d\n", (*(cont+(inf-k)*2*k+r)+1));
          *(hist_t_inf+(*(cont+(inf-k)*2*k+r)+1)-k) = t; //Guardo el tiempo de contagio del sujeto.
          cant_inf = cant_inf + 1; //Agrego un infectado.
        }
        else {
          //printf("Volvió a tener contacto con %d\n", *(cont+(inf-k)*2*k+r));
        }
        for (i=0;i<k;i++) { //Mantiene la periodicidad.
          *(pac+i) = *(pac+l+i); //Toma los valores del final.
          *(pac+l+k+i) = *(pac+k+i); //Toma los valores del principio.
        }
      }
      //cant_inf = contar_inf(); Cuento la nueva cantidad de pacientes.
      t = t + (float)1/(float)cant_inf;
      inf = k + (rand()%l);

      while (*(pac+inf) >= 0 && cant_inf>0) {
        inf = k + (rand()%l);
      }
    }
//--------------------------------------------------------------------------
  }

  free(pac);
  free(cont);
  free(hist_t_inf);

  return n_ref;
}
