#include "ListaS.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

nodoLS::nodoLS(char * nombre, int punteo)
{
	this->nombre = nombre;
	this->punteo = punteo;
	this->sig = 0;
}
ListaS::ListaS(){
	this->primero = 0;
	
}//insertar al inicio en la lista
void ListaS::insertarOrdenada(char*nombre, int punteo){
	nodoLS *nuevo= new nodoLS(nombre, punteo);
	if(primero == 0){
		primero = nuevo;
		tamLS = 0;	
	}
	else{
		bool i =true;
		nodoLS *aux = primero;
		
		while(i==true){
			if(punteo > primero->punteo){
				nuevo->sig = primero;
				primero = nuevo;
				tamLS++;
				i=false;
			}
			else {
				if(aux->sig != 0){
					if(punteo< aux->punteo && punteo>aux->sig->punteo){
						nuevo->sig =aux->sig;
						aux->sig = nuevo;
						tamLS++;
						i=false;
					}else{
						
						aux = aux->sig;
					}
				}
				else{
					aux->sig = nuevo;
					tamLS++;
					i= false;
				}
			}
		}
		
		
	}
}
void ListaS::print(){
	nodoLS *aux = primero;
	while(aux->sig != 0){
		cout<<aux->punteo;
		aux = aux->sig;
	}
	cout<<aux->punteo<<endl;
	
}
void ListaS::reporte(){
	ofstream reporte;
	reporte.open("RepScoreboard.dot", ios::out);
	if(reporte.fail()){
		cout<<"Reporte no creado"<<endl;
		
	}else{
		reporte<<"digraph G{\n";
		reporte<<"rankdir = LR;\n";
		reporte<<"node [shape= record];\n";
		nodoLS* aux = primero;
		for(int i= 0; i<=tamLS; i++){
			if(aux->sig != 0){
				reporte<<i;
				reporte<<"[label = \"{<ref> | <data>";
				reporte<<aux->nombre;
				reporte<<",";
				reporte<<aux->punteo;
				reporte<<" | }\"]\n";
				reporte<<i+1;
				reporte<<"[label = \"{<ref> | <data>";
				reporte<<aux->sig->nombre;
				reporte<<",";
				reporte<<aux->sig->punteo;
				reporte<<" | }\"]\n";
				reporte<<i;
				reporte<<"->";
				reporte<<i+1;
				reporte<<"\n";
				aux = aux->sig;
			}
			
			
		}
		reporte<<"}";
		reporte.close();
		system("dot -Tpng RepScoreboard.dot -o RepScoreboard.png");
		system("RepScoreboard.png &");
	}
}
void ListaS::reporteJugador(char* nombre){
	ofstream reporte;
	reporte.open("RepJugador.dot", ios::out);
	if(reporte.fail()){
		cout<<"reporte no creado"<<endl;
		
	}else{
		reporte<<"digraph G{\n";
		reporte<<"rankdir = LR;\n";
		reporte<<"node [shape= record];\n";
		nodoLS* aux = primero;
		for(int i= 0; i<=tamLS; i++){
			if(aux->sig != 0&&aux->nombre == nombre){
				reporte<<aux->punteo;
				reporte<<"->";
				reporte<<aux->sig->punteo;
				reporte<<"\n";
				aux = aux->sig;
			}
			else{
				aux = aux->sig;
			}
		}
		reporte<<"}";
		reporte.close();
		system("dot -Tpng RepJugador.dot -o RepJugador.png");
		system("RepJugador.png &");
	}
}

