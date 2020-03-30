#include "Metodos.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <string.h>
using namespace std;


void Metodos::menu(){
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
int Metodos::PuntajeHorizontal(string palabra, int fila){
	int p = palabra.size();
	int puntaje;
	NodoLD *aux ;
	Encabezado *eFila = matriz->eFilas->getEncabezado(fila);
	NodoM *actual= eFila->acceso;
	string letra;
	for(int i=0; i<=p; i++){
		letra = letra + palabra[i];
		aux = fichasCopia->primero;
		aux->sig->letra;
		
		while(letra != aux->letra&&aux->sig != 0){
			
				aux = aux->sig;
		}
		if(letra== aux->letra){
			while(letra != actual->valor && actual->derecha != 0){
				actual = actual->derecha;
			}
			if(letra == actual->valor && actual->valorAnt == "dobles"){
				puntaje = 2*aux->puntaje + puntaje;//revisar
			}else{
				puntaje = puntaje+aux->puntaje;//revisar
			}
			
		}
		letra = "";
	}
	return puntaje;
}
int Metodos::PuntajeVertical(string palabra, int columna){
	int p = palabra.size();
	int puntaje;// revisar
	NodoLD *aux ;
	Encabezado *eColumna = matriz->eColumnas->getEncabezado(columna);
	NodoM *actual= eColumna->acceso;
	string letra;
	for(int i=0; i<=p; i++){
		letra = letra + palabra[i];
		aux = fichasCopia->primero;
		while(letra != aux->letra && aux->sig != 0){
			aux = aux->sig;
		}
		if(letra== aux->letra){
			while(letra != actual->valor && actual->abajo != 0){
				actual = actual->abajo;
			}
			if(letra == actual->valor && actual->valorAnt == "dobles"){
				puntaje = 2*aux->puntaje + puntaje;
			}else{
				puntaje = puntaje+aux->puntaje;//revisar
			}
			
		}
		letra = "";
	}
	return puntaje;
}
void Metodos::ValidarPalabraVertical(string palabra, int filaInicio, int filaFinal, int columna, Nodo *jugador){
	int p = palabra.size();
	NodoM *aux ;
	string c ;
	bool bandera = true;
	int fila = filaInicio;
	filaFinal = filaInicio + filaFinal;
	for(int i = 0; i<p; i++){
		while(filaInicio < filaFinal){
			//matriz->reporte(); REVISAR :-(
			aux = matriz->buscar(11,9);
			aux->valor;
			aux= matriz->buscar(filaInicio, columna);
			c = c+palabra[i];
			char *d =new char[c.length()+1];
			strcpy(d, c.c_str());
			char *pa=strtok(d, "");
			matriz->recorrerFilas();
			if(aux == NULL){
				
				matriz->insertar(filaInicio, columna, pa);
				matriz->recorrerFilas();
				c = "";
				filaInicio++;
				i++;
				
			}
			else{
				matriz->recorrerFilas();
				if(aux->valor == "dobles" || aux->valor =="triples"){
					aux->valorAnt = aux->valor;
					aux->valor = pa;
					c = "";
					filaInicio++;
					i++;
					
				}else{
					if(c!=aux->valor){
						cout<<"Casilla ocupada " ;
						cout<<aux->valor;
						cout<<"fila";
						cout<<aux->fila;
						cout<<"Columna";
						cout<<aux->columna;
						c = "";
						i=p;
						bandera = false;
						break;
					}else{
						aux->valorAnt = aux->valor;
						c = "";
						filaInicio++;
						i++;
					}
				}
			}
		}
	}
	if(bandera == true){
		
		Encabezado * eColumna =matriz->eColumnas->getEncabezado(columna);
		NodoM *aux = eColumna->acceso;
		while(aux->abajo != NULL &&(aux->abajo->valor!="dobles"|| aux->abajo->valor!="triples")){
		//	if((aux->valor != "dobles"&& aux->valor!="triples")){
				
				c = c+ aux->valor;
				aux = aux->abajo;
		//	}else{
		//		aux = aux->abajo;
		//	}
			
			
		}
		if(aux->valor != "dobles"&& aux->valor != "triples" && aux->valor != 0)
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
			jugador->jugador->fichasJugador->insertar(actualC->letra,1, actualC->punteo);
			fichasDisponibles->eliminar();
		}
		
		cout<<"PALABRA INGRESADA \n";
		jugador->jugador->puntaje = jugador->jugador->puntaje + PuntajeVertical(c,columna);
		cout<<"Puntaje de "<<jugador->jugador->puntaje<<endl;
		
	}else{
		NodoLD *actual;
		cout<<"PALABRA NO INGRESADA \n";
		for(int i= 0; i<=p; i++){
			
			while(fila <= filaFinal){
				c= palabra[i];
				aux= matriz->buscar(fila, columna);
				char *d =new char[c.length()+1];
				strcpy(d, c.c_str());
				char *pa=strtok(d,"");
				if(aux->valorAnt == 0){
					matriz->eliminar(fila, columna);
					actual = fichasCopia->buscar(pa);
					jugador->jugador->fichasJugador->insertar(pa,1,actual->puntaje);
					fila++;
					i++;
				}
				else{
					aux->valor = aux->valorAnt;
					actual = fichasCopia->buscar(pa);
					jugador->jugador->fichasJugador->insertar(pa,1,actual->puntaje);
					fila++;
					i++;
					
				}
			}
		}
	}
}
void Metodos::insertarFichas(ListaD *fichas){
	fichas->insertar("A",12,1);
	fichas->insertar("E",12,1);
	fichas->insertar("O",9,1);
	fichas->insertar("I",6,1);
	fichas->insertar("S",6,1);
	fichas->insertar("N",5,1);
	fichas->insertar("L",4,1);
	fichas->insertar("R",5,1);
	fichas->insertar("U",5,1);
	fichas->insertar("T",4,1);
	fichas->insertar("D",5,2);
	fichas->insertar("G",2,2);
	fichas->insertar("C",4,3);
	fichas->insertar("B",2,3);
	fichas->insertar("M",2,3);
	fichas->insertar("P",2,3);
	fichas->insertar("H",2,4);
	fichas->insertar("F",1,4);
	fichas->insertar("V",1,4);
	fichas->insertar("Y",1,4);
	fichas->insertar("Q",1,5);
	fichas->insertar("J",1,8);
	fichas->insertar("Ñ",1,8);
	fichas->insertar("X",1,8);
	fichas->insertar("Z",1,10);
}
int Metodos::PosicionRandom(){
	int posicion;
	srand(time(NULL));
	posicion= rand()%25;
	
	return posicion;
}
void Metodos::RepartirFichas(Nodo *j1, Nodo *j2){
	NodoLD *aux = fichas->primero;
	int ingresada=0;
	int i=0;
	int pos;
	while(ingresada<7){
		pos = PosicionRandom();
		aux = fichas->primero;
		while( i!= pos && i<fichas->tamLD ){
			aux = aux->sig;
			i++;
		}
		if(aux->cantidad != 0){
			
			j1->jugador->fichasJugador->insertar(aux->letra, 1, aux->puntaje);
			fichas->eliminarCantidad(aux->letra,1);
			ingresada++;
			
		}
		i=0;
	}
		
	
	ingresada =0;
	while(ingresada<7){
		pos = PosicionRandom();
		aux = fichas->primero;
		while( i!= pos&& i<fichas->tamLD){
			aux = aux->sig;
			i++;
		}	
		if(aux->cantidad != 0){
			j2->jugador->fichasJugador->insertar(aux->letra, 1, aux->puntaje);
			
			fichas->eliminarCantidad(aux->letra,1);
			ingresada++;
		}
		i=0;
	}
	
	while(fichas->tamLD>0){
		aux = fichas->primero;
		if(fichas->tamLD >0)
			pos = PosicionRandom();
		while(i != pos&& i<fichas->tamLD){
			aux = aux->sig;
			i++;
		}
		fichasDisponibles->tamC;
		fichasDisponibles->insertar(aux->letra,aux->puntaje);
		fichas->eliminarCantidad(aux->letra,1);
		i=0;
	}
	fichasDisponibles->insertar(fichas->primero->letra,fichas->primero->puntaje);
	fichas->eliminarCantidad(fichas->primero->letra,1);
}
bool Metodos::turno(string palabra,Nodo* jugador){
	int p = palabra.size();
	string c;
	bool correcta = true;
	
	int i=0;
	while(correcta== true && i<=p){
		c = c+palabra[i];
		char *d =new char[c.length()+1];
		strcpy(d, c.c_str());
		char *pa=strtok(d, "");
		NodoLD *aux = jugador->jugador->fichasJugador->primero;
		while(c != aux->letra && aux->sig != 0){
			aux = aux->sig;
		}
		if(c == aux->letra){
			c="";
			i++;
		}
		else{
			if(i!=p)
				correcta=false;
			i++;
		}
	}
	i=0;
	if(correcta == false){
		cout<<"VERIFICAR FICHAS\n";
		return false;
	}
	while(correcta==true && i<=p){
		c = palabra[i];
		char *d =new char[c.length()+1];
		strcpy(d, c.c_str());
		char *pa=strtok(d, "");
		NodoLD *aux = jugador->jugador->fichasJugador->primero;
		while(c!=aux->letra && aux->sig !=0){
			aux = aux->sig;
		}
		if(c == aux->letra){
			jugador->jugador->fichasJugador->eliminarCantidad(aux->letra,1);
			c="";
			i++;
		}else {
			if(i!=p)
				correcta=false;
			i++;
			return true;
				//cout<<"SIGUIENTE TURNO\n";
				
			
			
				
		}
	}
}
void Metodos::sdf(string palabra, Nodo *Jactual, Nodo *Jsiguiente){
	int p, columna,fila, opcion;
	cout<<"TURNO DE: ";
	cout<<Jactual->info<<"\n";
		Jactual->jugador->fichasJugador->print();
		cout<<"1.INGRESAR PALABRA\n";
		cout<<"2. CAMBIAR FICHAS\n";
		cout<<"3. TERMINAR JUEGO\n";
		cin>>opcion;
		if(opcion==2){
			cout<<"INGRESAR LETRAS\n";
			cin>>palabra;
			CambiarFichas(palabra,Jactual);
		}else if(opcion ==1){
			cout<<"INGRESAR PALABRA\n";
			cin>>palabra;
			p = palabra.size();
			bool t;
			t=turno(palabra,Jactual);
			if(t==true){
				cout<<"INGRESAR FILA Y COLUMNA DE INICIO\n";
				cin>>fila;
				cin>>columna;
				cout<<"1. HORIZONTAL\n";
				cout<<"2. VERTICAL\n";
				cin>>opcion;
				if(opcion==1){
					ValidarPalabraHorizontal(palabra,columna, p, fila, Jactual);
					
					matriz->reporte();
				}else if(opcion == 2){
					ValidarPalabraVertical(palabra, fila, p, columna, Jactual);
					ValidarPalabraVertical("HOLA",3,6,10, j1);
					ValidarPalabraHorizontal("MUNDO",6,10,4, j1);
					matriz->reporte();
				}
			
			}
		}
		else if(opcion ==3){
			scoreboard->insertarOrdenada(Jactual->jugador->nombre, Jactual->jugador->puntaje);
			scoreboard->insertarOrdenada(Jsiguiente->jugador->nombre, Jsiguiente->jugador->puntaje);
			menu();
		}
		
}
void Metodos::CambiarFichas(string letras, Nodo * jugador){
	int l = letras.size();
	string c;
	for(int i = 0; i<= l; i++){
		c = letras[i];
		char *d =new char[c.length()+1];
		strcpy(d, c.c_str());
		char *pa=strtok(d, "");
		NodoLD*aux = jugador->jugador->fichasJugador->buscar(pa);
		if(aux!=NULL){
			fichasDisponibles->insertar(aux->letra, aux->puntaje);
			jugador->jugador->fichasJugador->eliminarCantidad(aux->letra,1);
			nodoC*nuevo = fichasDisponibles->eliminar();
			jugador->jugador->fichasJugador->insertar(nuevo->letra, 1, nuevo->punteo);
		}
		
	}
}

