#include <stdio.h>
#include <string.h>
#define MAX 100
// Esctructura de la base de datos vuelos
struct VL{
	char desde[20];
	char hacia[20];
	int distancia;
	char visitado;
} vuelos [MAX]; // Array de estructura de la bd

int pos_ult=0; // numero de entradas en la bd vuelos
int encuentra_pos = 0; // indice de busqueda en la bd vuelos
int cabeza_pila = 0; // ultima posicion de la pila

struct pila{
	char desde[20];
	char hacia[20];
	int dist;
} pila_rt[MAX]; // pila de rutas de vuelos
void inicia();
void ruta(char *hacia);
int unidas (char *desde, char *hacia);
int encuentra(char *desde, char *cualquier_lugar);
void hay_vuelo(char *desde, char *hacia);
void declara_vuelo(char *desde, char *hacia, int dist);
void mete_pila(char *desde, char *hacia, int dist);
void saca_pila(char *desde, char *hacia, int *dist);

int main(void) {
  printf("Hello World\n");
	char desde[20], hacia[20];
	printf("Desde? = ");
	gets(desde);
	printf("Hacia? = ");
	gets(hacia);
	hay_vuelo(desde,hacia);
	ruta(hacia);
  return 0;
}
//Colocar data dentro de la BD vuelos
void declara_vuelo(char *desde, char *hacia, int dist){
	if(pos_ult<MAX){
		strcpy(vuelos[pos_ult]. desde, desde);
		strcpy(vuelos[pos_ult].hacia, hacia);
		vuelos[pos_ult].distancia = dist;
		vuelos[pos_ult].visitado = 0;
		pos_ult++;
	}
	else
		printf("Base de datos de vuelos llena\n");
}

void inicia(){
	declara_vuelo("Panama", "Cocle", 1000);
	declara_vuelo("Cocle", "Veraguas", 1000);
	declara_vuelo("Panama", "Colon", 800);
	declara_vuelo("Panama", "Veraguas", 1900);
	declara_vuelo("Colon", "Bocas del Toro", 1500);
	declara_vuelo("Colon", "Chiriqui", 1800);
	declara_vuelo("Colon", "Cocle", 500);
	declara_vuelo("Veraguas", "Herrera", 1000);
	declara_vuelo("Veraguas", "Los Santos", 1500);
	declara_vuelo("Los Santos", "Chiriqui", 1500);
	declara_vuelo("Veraguas", "Chiriqui", 1000);
}
//Muestra la ruta y la distancia
void ruta(char *hacia){
	int dist = 0;
	int t = 0;
	while(t<cabeza_pila) {
		printf ("%s hacia", pila_rt[t].desde);
		dist+=pila_rt[t].dist;
	}
	printf("%s\n", hacia);
	printf("La distancia es: %d\n", dist);
	t++;
}

/* SI HAY CONEXIÓN ENTRE DESDE Y HACIA, ENTONCES DEVUELVE LA
DISTANCIA DEL VUELO. SI NO, DEVUELVEO */
int unidas (char *desde, char *hacia){
	register int t;
	for (t=pos_ult-1;t>-1;t--){
		if (!strcmp(vuelos[t].desde,desde) && !strcmp(vuelos[t].hacia,hacia))
			return vuelos[t].distancia;
	}
	return 0;
} /* no encontrado */
/* DADO UN DESDE, ENCUENTRA CUALQUIER_LUGAR */
int encuentra(char *desde, char *cualquier_lugar){
	encuentra_pos = 0;
	while( encuentra_pos < pos_ult ){
		if(!strcmp(vuelos[encuentra_pos].desde, desde)&& !vuelos[encuentra_pos].visitado){
			strcpy(cualquier_lugar, vuelos[encuentra_pos].hacia);
			vuelos[encuentra_pos].visitado = 1;
			return vuelos[encuentra_pos].distancia;
		}
		encuentra_pos++;
	}
	return 0;
}
//Determina si hay una ruta entre desde y distancia
void hay_vuelo(char *desde, char *hacia){
	int d, dist;
	char cualquier_lugar[20];
	if(d == unidas(desde, hacia)){
		mete_pila(desde, hacia, d);
		return;
	}
	if( dist == encuentra(desde, cualquier_lugar)){
		mete_pila(desde, hacia, d);
		hay_vuelo(cualquier_lugar, hacia);
	}
	else if (cabeza_pila>0){
		saca_pila(desde, hacia, &dist);
		hay_vuelo(desde, hacia);
	}
}
//Rutinas de pila
void mete_pila(char *desde, char *hacia, int dist){
	if(cabeza_pila < MAX){
		strcpy(pila_rt[cabeza_pila].desde, desde);
		strcpy(pila_rt[cabeza_pila].hacia, hacia);
		pila_rt[cabeza_pila].dist = dist;
		cabeza_pila++;
	}
	else printf("Pila llena \n");
}

void saca_pila(char *desde, char *hacia, int *dist){
	if (cabeza_pila > 0){
		cabeza_pila--;
		strcpy(desde, pila_rt[cabeza_pila].desde);
		strcpy(hacia, pila_rt[cabeza_pila].hacia);
		*dist = pila_rt[cabeza_pila].dist;
	}
	else printf("Pila vacia\n");
}