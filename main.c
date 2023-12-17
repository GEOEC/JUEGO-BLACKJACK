
#include <stdio.h>
#include <stdlib.h>
#include "blackjack.h"

int main(void) {
  int opcion;
  menu();
  scanf("%d", &opcion);

  while (opcion != 4){
  if (opcion == 1){
    jugarPartida();
    }
  else if (opcion == 2){
    cargarPartida();
  }
    fflush(stdin);
    menu();
    scanf("%d", &opcion);
  }
  printf("GRACIAS POR JUGAR");

}
