#include "ListaS.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

nodoLS::nodoLS(char * nombre, int puntos)
{
	this->nombre = nombre;
	this->puntos = puntos;
	this->sig = 0;
}
ListaS::ListaS(){
	this->primero = 0;
	
}//insertar al inicio en la lista
void ListaS::insertarOrdenada(char*nombre, int puntos){
	nodoLS *nuevo= new nodoLS(nombre, puntos);
	if(primero == 0){
		primero = nuevo;
		tamLS = 0;	
	}
	else{
		bool i =true;
		nodoLS *aux = primero;
		
		while(i==true){
			if(puntos > primero->puntos){
				nuevo->sig = primero;
				primero = nuevo;
				tamLS++;
				i=false;
			}
			else {
				if(aux->sig != 0){
					if(puntos< aux->puntos && puntos>aux->sig->puntos){
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
		cout<<aux->puntos;
		aux = aux->sig;
	}
	cout<<aux->puntos<<endl;
	
}
void ListaS::reporte(){
	ofstream reporte;
	reporte.open("RepScoreboard.dot", ios::out);
	if(reporte.fail()){
		cout<<"No se creo el reporte"<<endl;
		
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
				reporte<<aux->puntos;
				reporte<<" | }\"]\n";
				reporte<<i+1;
				reporte<<"[label = \"{<ref> | <data>";
				reporte<<aux->sig->nombre;
				reporte<<",";
				reporte<<aux->sig->puntos;
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
		cout<<"No se creo el reporte"<<endl;
		
	}else{
		reporte<<"digraph G{\n";
		reporte<<"rankdir = LR;\n";
		reporte<<"node [shape= record];\n";
		nodoLS* aux = primero;
		for(int i= 0; i<=tamLS; i++){
			if(aux->sig != 0&&aux->nombre == nombre){
				reporte<<aux->puntos;
				reporte<<"->";
				reporte<<aux->sig->puntos;
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

