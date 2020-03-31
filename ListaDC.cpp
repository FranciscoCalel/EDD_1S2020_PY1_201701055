#include "ListaDC.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


nodoldc::nodoldc(string palabra)
{
	this->palabra = palabra;
	this->sig = 0;
	this->ant = 0;	
}
ListaDC::ListaDC(){
	this->ultimo = 0;
	this->primero = 0;
	this->tamaLC = -1;
}

void ListaDC::insertar(string palabra){
	nodoldc * nuevo= new nodoldc(palabra);
	if(primero == 0){
		primero = nuevo;
		ultimo = nuevo;
		primero->ant = ultimo;
		ultimo->sig = primero;
		primero->sig = ultimo;
		tamaLC = 0;
	}
	else{
		primero->ant = nuevo;
		ultimo->sig = nuevo;
		nuevo->ant = ultimo;
		nuevo->sig = primero;
		ultimo = nuevo;
		tamaLC++;
	}
}
void ListaDC::print(){
	if(tamaLC == -1)
		cout<<"Lista Vacia";
	else{
		nodoldc *aux = primero;
		while(aux != ultimo){
			cout<<aux->palabra<<endl;
			aux = aux->sig;
		}
		cout<<aux->palabra<<endl;
		
	}
}
void ListaDC::reporte(){
	ofstream reporte;
	reporte.open("RepDiccionario.dot", ios::out);
	if(reporte.fail()){
		cout<<"No se creo el reporte"<<endl;
		
	}
	else{
		reporte<<"digraph G{\n";
		reporte<<"rankdir = LR;\n";
		reporte<<"node [shape= record];\n";
		nodoldc* aux = primero;
		for (int i = 0; i <= tamaLC; i++) {
			reporte<<aux->palabra;
			reporte<<"->";
			reporte<<aux->sig->palabra;
			reporte<<"\n";
			reporte<<aux->ant->palabra;
			reporte<<"->";
			reporte<<aux->ant->ant->palabra;
			reporte<<"\n";
			
			aux = aux->sig;
		}
		reporte<<"}";
		reporte.close();
		system("dot -Tpng RepDiccionario.dot -o RepDiccionario.png");
		system("RepDiccionario.png &");
	}
	
}

