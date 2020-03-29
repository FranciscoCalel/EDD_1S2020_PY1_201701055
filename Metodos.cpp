#include "Operaciones.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
using namespace std;


void Operaciones::menu(){
	system("cls");
	string entrada;
	int opcion;
	cout<<"1. LECTURA DE ARCHIVO\n";
	cout<<"2. JUGAR\n";
	cout<<"3. Reportes\n";
	cin>>opcion;
	switch(opcion){
		case 1:
			system("cls");
			cout<<"INGRESAR NOMBRE DE ARCHIVO\n";
			cin>>entrada;
			entrada = entrada +".json";
			LecturaDeArchivo(entrada);
			matriz->reporte();
			menu();
			break;
		case 2:
			system("cls");
			cout<<"1. INGRESAR NUEVO JUGADOR\n";
			cout<<"2. SELECCIONAR JUGADOR\n";
			cin>>opcion;
			if(opcion ==1){
				IngresarJugador();
				
			}else if(opcion == 2){
				usuaios->insertar("franc");
				usuaios->insertar("lol");
			
				SeleccionarJugador();
			}
				
			
			break;
		case 3:
			system("cls");
			cout<<"1.  DICCIONARIO \n";
			cout<<"2.  FICHAS DISPPONIBLES \n";
			cout<<"3.  JUGADORES \n";
			cout<<"4.  RECORRIDO PREORDEN \n";
			cout<<"5.  RECORRIDO INORDEN \n";
			cout<<"6.  RECORRIDO POSTORDEN \n";
			cout<<"7.  PUNTAJE POR JUGADOR \n";
			cout<<"8.  SCORE BOARD \n";
			cout<<"9.  TABLERO \n";
			cout<<"10. FICHAS DE JUGADOR 1 \n";
			cout<<"11. FICHAS DE JUGADOR 2 \n";
			cin>>opcion;
			reportes(opcion, j1,j2);
			menu();
			break;
	}
