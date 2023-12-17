#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "blackjack.h"

const char *tipo_carta[] = {"corazones", "diamantes", "picas", "treboles"};
const char *num_carta[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K","A"};

int numeroGenerado;
int puntosCarta(const char *carta);
int generarCarta();
void menuSecundario();
void mostrarGanador();
void guardarPartida();
char* obtenerFecha();

struct jugador jugadores[MAX_JUGADORES];

void menu(){
    printf("BIENVENIDO AL BLACKJACK\n");
    printf("-------------------------\n");
    printf("1. Juego Nuevo\n");
    printf("2. Cargar Partida\n");
    printf("3. Guardar Partida\n");
    printf("4. Salir\n");
    printf("-------------------------\n");
    printf("Ingrese la opcion deseada (digitar el numero correspondiente)\n");
}

void jugarPartida(){
int n_jugadores;

  printf("Introduzca la cantidad de jugadores que van a jugar(2-4): \n");
  scanf("%d", &n_jugadores);

  while(n_jugadores <= 1 || n_jugadores > 4){

    printf("El numero de jugadores es invalido, ingrese otro numero: \n");
    scanf("%d", &n_jugadores);
      }

  getchar();
  for(int i = 1; i <= n_jugadores; i++){
    struct jugador j;
    printf("Ingrese el nombre del jugador %d: \n", i);
    fgets(j.nombre, sizeof(j.nombre), stdin);
    jugadores[i-1]=j;

  }

  for(int i = 0; i < n_jugadores; i++){
    printf("TURNO DE %s\n", jugadores[i].nombre);
    int puntuacion=0;

    puntuacion=puntuacion+generarCarta();
    puntuacion=puntuacion+generarCarta();

    printf("Tu puntuacion es: %d\n", puntuacion);
    int opcion;
    fflush(stdin);
    menuSecundario();
    scanf("%d", &opcion);

    while (opcion != 2 && puntuacion != 0){
      if(opcion == 1){
        puntuacion=puntuacion+generarCarta();
        if (puntuacion > 21){
          puntuacion=0;
          printf("TE HAS PASADO");
        }
        printf("PUNTOS TOTALES: %d\n", puntuacion);
      }
      if (puntuacion !=0){
        fflush(stdin);
        menuSecundario();
        scanf("%d", &opcion);
      }
    }
    jugadores[i].puntos=puntuacion;
  }
  mostrarGanador(n_jugadores);
  guardarPartida(n_jugadores);
}



int generarCarta(){
  int n_tipo_carta = rand()%4;
  int n_num_carta = rand()%13;

  printf("--------------\n");
  printf("%s\n\n",num_carta[n_num_carta]);
  printf("%s\n\n",tipo_carta[n_tipo_carta]);
  printf("\t\t\t%s\n\n",num_carta[n_num_carta]);
  printf("--------------\n");

  const char *carta = num_carta[n_num_carta];
  int valor=puntosCarta(carta);

  return valor;
}



int puntosCarta(const char *carta){
  int valor=0;

  if(strcmp(carta,"2")==0){
    valor=2;
  }
  else if(strcmp(carta,"3")==0){
    valor=3;
  }
  else if(strcmp(carta,"4")==0){
     valor=4;
  }
  else if(strcmp(carta,"5")==0){
     valor=5;
  }
  else if(strcmp(carta,"6")==0){
     valor=6;
  }
  else if(strcmp(carta,"7")==0){
     valor=7;
  }
  else if(strcmp(carta,"8")==0){
     valor=8;
  }
  else if(strcmp(carta,"9")==0){
     valor=9;
  }
  else if(strcmp(carta,"10")==0){
     valor=10;
  }
  else if(strcmp(carta,"J")==0){
     valor=10;
  }
  else if(strcmp(carta,"Q")==0){
     valor=10;
  }
  else if(strcmp(carta,"K")==0){
     valor=10;
  }
  else if(strcmp(carta,"A")==0){
     valor=11;
  }

  return valor;
}


void menuSecundario(){
  printf("Seleccione una opcion (Digite el numero)\n");
  printf("1. Dame Carta\n");
  printf("2. Terminar Turno\n");
}

void mostrarGanador(int n_jugadores){
  int punt_max=0;
  int index_max;

  for(int i = 0; i < n_jugadores; i++){
    if(jugadores[i].puntos > punt_max){
      index_max=i;
      punt_max=jugadores[i].puntos;
    }
  }
  printf("El ganador es: %s con una puntuacion de: %d \n", jugadores[index_max].nombre, jugadores[index_max].puntos);
  printf("..........................................\n\n");
}

void guardarPartida(int n_jugadores){
  FILE*f;
  f=fopen("partida.txt","w");
  char* fecha= obtenerFecha();

  fprintf(f,"\nFecha:%s--",fecha);
  for(int i = 0; i < n_jugadores-1; i++){
    fprintf(f,"Nombre: %s - Puntos: %d\n",jugadores[i].nombre,jugadores[i].puntos);
  }
  fprintf(f,"Nombre: %s - Puntos: %d\n",jugadores[n_jugadores-1].nombre,jugadores[n_jugadores-1].puntos);
  fclose(f);
}

char* obtenerFecha(){
  time_t t;
  struct tm *tm;
  char formateada[100];

  t=time(NULL);
  tm=localtime(&t);
  strftime(formateada,100,"%d/%m/%y %H:%M:%S",tm);
  char *fecha = malloc(sizeof(char)*100);
  strcpy(fecha,formateada);

  return fecha;
}

void cargarPartida(){

  FILE*f;
  f=fopen("partida.txt","r");
  char cadena[255];

  while(feof(f)==0){
    fgets(cadena,255,f);
    printf("%s",cadena);
  }
  printf("\n\n");
  fclose(f);
}





