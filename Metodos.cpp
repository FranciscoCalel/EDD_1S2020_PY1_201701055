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
	void Metodos::jugar(Nodo *j1, Nodo * j2){
	bool juego = true;
	bool turnoJ1= true;
	bool turnoJ2 = false;
	while(juego == true){
		string palabra;
		if(turnoJ1 == true){
			system("cls");
			sdf(palabra, j1, j2);
			turnoJ1 = false;
			turnoJ2 = true;
		}else if(turnoJ2 == true){
			system("cls");
			sdf(palabra, j2, j1);
			turnoJ2 = false;
			turnoJ1 = true;
		}
	}
}


void Metodos::SeleccionarJugador(){
	char *nombre;
	
	jugador->preOrden(jugador->raiz);
	cout<<"INGRESAR NOMBRE JUGADOR 1 \n";
	cin>>nombre;
	j1 =jugador->buscar(nombre);
	if(j1== NULL){
		
		cout<<"JUGADOR NO ENCONTRADO\n";
		SeleccionarJugador();
	}
	
	cout<<"INGRESAR NOMBRE JUGADOR 2 \n";
	cin>>nombre;
	j2 = jugador->buscar(nombre);
	
	while(j2== NULL){
		cout<<"JUGADOR NO ENCONTRADO\n";
		cout<<"INGRESAR NOMBRE JUGADOR 2 \n";
		cin>>nombre;
		j2 = jugador->buscar(nombre);
	}
	insertarFichas(fichas);
	insertarFichas(fichasCopia);
	RepartirFichas(j1, j2);
	system("cls");
	jugar(j1,j2);
	
	
}
void Metodos::IngresarJugador(){
	char *nombre;
	cout<<"INGRESAR NOMBRE JUGADOR 1\n";
	cin>>nombre;
	jugador->insertar(nombre);
	
	cout<<"INGRESAR NOMBRE JUGADOR 2\n";
	cin>>nombre;
	jugador->insertar(nombre);
	
	menu();
	
	
}
void Metodos::reportes(int opcion, Nodo *j1, Nodo *j2){
	char * nombre;
	Nodo *aux;
	switch(opcion){
		case 1:
			listaDiccionario->reporte();
			break;
		case 2:
			fichasDisponibles->reporte();
			break;
		case 3:
			jugador->reporte();
			break;
		case 4:
			jugador->reportePreorden();
			break;
		case 5:
			jugador->reporteInorden();
			break;
		case 6:
			jugador->reportePostorden();
			break;
		case 7:
			cout<<"INGRESAR NOMBRE DE JUGADOR\n";
			cin>>nombre;
			aux = jugador->buscar(nombre);
			if(aux!=NULL){
				scoreboard->reporteJugador(nombre);
			}
			else{
				cout<<"USUARIO NO ENCONTRADO\n";
			}
			
			break;
		case 8:
			scoreboard->reporte();
			break;
		case 9:
			matriz->reporte();
			break;
		case 10:
			j1->jugador->fichasJugador->reporte();
			break;
		case 11:
			j2->jugador->fichasJugador
			->reporte();
			break;
	}
}
void Metodos::LecturaDeArchivo(string archivo){
	ifstream file(archivo.c_str(), ios::out);
	if(!file.fail()){
		json j3;
		file>>j3;
		dimension =j3.at("dimension");
		for(int j=0; j<1;j++){
			int x,y;
			for(int j= 0; j<j3.at("casillas").at("dobles").size();j++){
				 x = j3.at("casillas").at("dobles")[j].at("x");
				 y =j3.at("casillas").at("dobles")[j].at("y");
				matriz->insertar(x,y,"dobles");
			}
			
			for(int j= 0; j<j3.at("casillas").at("triples").size();j++){
				x =j3.at("casillas").at("triples")[j].at("x");
				y= j3.at("casillas").at("triples")[j].at("y");
				matriz->insertar(x,y,"triples");
			}
			
		}
		for(int j= 0; j<j3.at("diccionario").size();j++){
			listaDiccionario->insertar(j3.at("diccionario")[j].at("palabra"));
			
		}
	}
}
void Metodos::ValidarPalabraHorizontal(string palabra, int columnaInicio, int columnaFinal, int fila, Nodo *jugador){
	int p = palabra.size();
	NodoM *aux ;
	string c ;
	bool bandera = true;
	int columna = columnaInicio;
	columnaFinal = columnaInicio +columnaFinal;
	for(int i = 0; i<p; i++){
		while(columnaInicio < columnaFinal){
				aux= matriz->buscar(fila, columnaInicio);
				c = c+palabra[i];
				char *d =new char[c.length()+1];
				strcpy(d, c.c_str());
				char *pa=strtok(d, "");
				if(aux == NULL){
					matriz->insertar(fila, columnaInicio, pa);
					c = "";
					columnaInicio++;
					i++;
				}
				else{
					
					if(aux->valor == "dobles" || aux->valor =="triples"){
						aux->valorAnt = aux->valor;
						aux->valor = pa;
						c = "";
						columnaInicio++;
						i++;
						
					}else{
						if(c!=aux->valor){
							cout<<"Casilla ocupada";
							c = "";
							i=p;
							bandera = false;
							break;
						}else{
							aux->valorAnt = aux->valor;
							c="";
							columnaInicio++;
							i++;
						}
						
					}
				}
		}
	}
	if(bandera == true){
		
		Encabezado * eFila =matriz->eFilas->getEncabezado(fila);
		NodoM *aux = eFila->acceso;
		while(aux->derecha != NULL&& (aux->derecha->valor != "dobles" || aux->derecha->valor != "triples")){
			c = c+ aux->valor;
			aux = aux->derecha;
		}
		if(aux->valor != "dobles" && aux->valor != "triples")
			c = c+ aux->valor;
		
	}
	
	nodoLC *aux1 = listaDiccionario->primero;
	
	while(aux1->palabra != c && aux1 != listaDiccionario->ultimo){
		aux1 = aux1->sig;
	}
	if(aux1->palabra == c){
		nodoC *actualC;
		for(int i = 0; i<=p; i++){
			actualC = fichasDisponibles->primero;
			
			jugador->jugador->fichasJugador->insertar(actualC->letra,1, actualC->punteo);//revisar
			fichasDisponibles->eliminar();
		}
		cout<<"PALABRA INGRESADA CORRECTAMENTE\n";
		jugador->jugador->puntaje = jugador->jugador->puntaje+PuntajeHorizontal(c,fila);
		cout<<"Puntaje de "<<jugador->jugador->puntaje;//revisar
	}else{
		NodoLD * actual;
		cout<<"PALABRA INGRESADA INCORRECTAMENTE\n";
		for(int i= 0; i<=p; i++){
			
			while(columna <= columnaFinal){
				c= palabra[i];
				aux= matriz->buscar(fila, columna);
				char *d =new char[c.length()+1];
				strcpy(d, c.c_str());
				char *pa=strtok(d,"");
				if(aux->valorAnt == 0){
					matriz->eliminar(fila, columna);
					actual = fichasCopia->buscar(pa);
					jugador->jugador->fichasJugador->insertar(pa,1,actual->puntaje);//revisaar
					fila++;
					i++;
				}
				else{
					aux->valor = aux->valorAnt;
					actual = fichasCopia->buscar(pa);
					jugador->jugador->fichasJugador->insertar(pa,1,actual->puntaje);//revisar
					fila++;
					i++;
					
				}
			}
		}
	}
	
	
}
