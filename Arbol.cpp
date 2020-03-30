#include "Arbol.h"
#include <sstream>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

//*******CONSTRUCTORES*******
Nodo::Nodo(char *info)
{
    this->info = (char*)malloc(sizeof(char) * strlen(info));
    strcpy(this->info, info);
    this->izq = NULL;
    this->der = NULL;
    this->jugador = new Jugador(info);
}
Jugador::Jugador(char *nombre){
	this->nombre = nombre;
	this->fichasJugador = new ListaD();
	this->puntaje = 0;
	
}

Arbol::Arbol()
{
    this->raiz = NULL;
}
//*******FIN CONSTRUCTORES*******


//*******BUSQUEDA*******
Nodo * Arbol::buscar(char * info)
{
    return buscar(this->raiz, info);
}

Nodo * Arbol::buscar(Nodo * actual, char *info)
{
	actual->info;
    if (actual == NULL)
    {
        return NULL;
    }

    int comparacion = strcmp(info, actual->info);
    if(comparacion == 0)
    {
    	actual->info;//
        return actual;
    }
    else
    {
    	actual->izq->info;
    	actual->der->info;
    	
    	
        return buscar(comparacion < 0 ? actual->izq : actual->der, info);
    }
}
//*******FIN BUSQUEDA*******

//*******INSERCION*******
bool Arbol::insertar(char *info)
{
    if (buscar(info) == NULL)
    {
        if(raiz == NULL)
        {
        	raiz->info;//
            raiz = new Nodo(info);
            return true;
        }
        else
        {
				raiz->info;
            return insertar(raiz, new Nodo(info));
        }
    }

    return false;
}

bool Arbol::insertar(Nodo * actual, Nodo * nuevo)
{
    if(strcmp(nuevo->info, actual->info) < 0)
    {
        if(actual->izq == NULL)
        {
            actual->izq = nuevo;
            return true;
        }
        else
        {
        	actual->izq->info;//
            return insertar(actual->izq, nuevo);
        }
    }
    else
    {
        if(actual->der == NULL)
        {
            actual->der = nuevo;
            return true;
        }
        else
        {
        	actual->der->info;//
            return insertar(actual->der, nuevo);
        }
    }
}
//*******FIN INSERCION*******

//*******RECORRIDOS*******
void Arbol::preOrden()
{
    cout << endl;
    cout << "*****Recorrido Pre-Orden*****\n" << endl;
    preOrden(raiz);
    cout << "*****Fin Recorrido Pre-Orden*****\n" << endl;
}

void Arbol::preOrden(Nodo *actual)
{
    if(actual != NULL)
    {
        cout << actual->info;
        cout<<"\n";
        preOrden(actual->izq);
        preOrden(actual->der);
    }
}

void Arbol::inOrden()
{
    cout << endl;
    cout << "*****Recorrido In-Orden*****" << endl;
    inOrden(raiz);
    cout << "*****Fin Recorrido In-Orden*****" << endl;
}

void Arbol::inOrden(Nodo *actual)
{
    if(actual != NULL)
    {
        inOrden(actual->izq);
        cout << actual->info << endl;
        inOrden(actual->der);
    }
}

void Arbol::postOrden()
{
    cout << endl;
    cout << "*****Recorrido PostOrden*****" << endl;
    postOrden(raiz);
    cout << "*****Fin Recorrido PostOrden*****" << endl;
}

void Arbol::postOrden(Nodo *actual)
{
    if(actual != NULL)
    {
        postOrden(actual->izq);
        postOrden(actual->der);
        cout << actual->info << endl;
    }
}
//*******FIN RECORRIDOS*******

//*******CALCULO DE ALTURA****
int Arbol::calcularAltura()
{
    if(this->raiz == NULL)
    {
        return 0;
    }
    else
    {
        return calcularAltura(raiz);
    }
}

int Arbol::calcularAltura(Nodo * actual)
{
    if(actual == NULL)
    {
        return 0;
    }
    else
    {
        int hi = calcularAltura(actual->izq);
        int hd = calcularAltura(actual->der);
        return (hi > hd ? hi : hd) + 1;
    }
}
//******FIN CALCULO DE ALTURA****

//******CALCULO DE NODOS HOJA****
int Arbol::getNodosHoja()
{
    if(this->raiz == NULL)
    {
        return 0;
    }
    else
    {
        return getNodosHoja(this->raiz);
    }
}

int Arbol::getNodosHoja(Nodo * actual)
{
    if(actual == NULL)
    {
        return 0;
    }
    else
    {
        if(actual->izq == NULL && actual->der == NULL)
        {
            return 1;
        }
        else
        {
            return getNodosHoja(actual->izq) + getNodosHoja(actual->der);
        }
    }
}

int entero =0;
string num;
//******FIN CALCULO DE NODOS HOJA***
Nodo * Arbol::reporte(Nodo *actual){
	stringstream s; // Creas el canal, contendr? el string
	s << entero;
	num = s.str();
	
	if(actual->izq != NULL){
		texto = texto + actual->info;
		texto = texto + "->";
		texto = texto + actual->izq->info;
		texto = texto + "\n";
		reporte(actual->izq);
	}
	else if(actual->izq == NULL){
		texto = texto + actual->info;
		texto = texto + "->";
		texto = texto +"NULL"+ num; 
		entero++;
		s.str(" ");
		s << entero;
		//cout<<s.str();
		num = s.str();
		texto = texto + "\n";
		
	}
	if(actual->der != NULL){
		texto = texto + actual->info;
		texto = texto + "->";
		texto = texto + actual->der->info;
		texto = texto + "\n";
		reporte(actual->der);
	}
	else if(actual->der == NULL ){
		texto = texto + actual->info;
		texto = texto + "->";
		texto = texto +"NULL"+ num; 
		entero++;
		s.str(" ");
		s << entero;
	//	cout<<s.str();
		num = s.str();
		texto = texto + "\n";
		
	}
	
	return actual;
	
}
void Arbol::reporte(){
	
	ofstream report;
	report.open("Reporte-Jugadores.dot", ios::out);
	if(report.fail()){
		exit(1);
	}
	else{
		texto = texto + "digraph G{\n";
		texto = texto + "node[shape=circle, style=filled, color = Gray95];\n";
		texto = texto + "edge[color =black]\n";
		Nodo *actual = raiz;
		reporte(actual);
		report<<texto;
		texto = "";
		report<<"}";
		report.close();
		system("dot -Tpng RepJugadores.dot -o RepJugadores.png");
		system("RepJugadores.png &");
	}
}
Nodo *Arbol::reportePreorden(Nodo *actual){
	if(actual != NULL)
    {
    	if(actual == raiz){
    		texto = texto + actual->info;
    		
	       	reportePreorden(actual->izq);
	        reportePreorden(actual->der);
		}
		else{
			texto = texto + "->";
			texto = texto + actual->info;
       		
       		reportePreorden(actual->izq);
        	reportePreorden(actual->der);
		}
        
    }
}
void Arbol::reportePreorden(){
	ofstream reporte;
	reporte.open("RepPreorden.dot", ios::out);
	if(reporte.fail()){
		exit(1);
	}else{
		reporte<<"digraph G{\n";
		reporte<<"rankdir = LR;\n";
		reporte<<"node [shape= record];\n";
		Nodo *actual = raiz;
		reportePreorden(actual);

		reporte<<texto;
		texto = "";
		reporte<<"}";
		reporte.close();
		system("dot -Tpng RepPreorden.dot -o RepPreorden.png");
		system("RepPreorden.png &");
	}
}
Nodo *Arbol::reporteInorden(Nodo *actual){
	if(actual != NULL)
    {
    	if(actual->der == NULL){
    		reporteInorden(actual->izq);
    		texto = texto + actual->info;
        	
        	
        	reporteInorden(actual->der);
		}else{
			reporteInorden(actual->izq);
			texto = texto + "->";
        	texto = texto + actual->info;
        	texto = texto + "->";
        	reporteInorden(actual->der);
		}
        
    }
}

void Arbol::reporteInorden(){
	ofstream reporte;
	reporte.open("RepInorden.dot", ios::out);
	if(reporte.fail()){
		exit(1);
	}else{
		reporte<<"digraph G{\n";
		reporte<<"rankdir = LR;\n";
		reporte<<"node [shape= record];\n";
		Nodo *actual = raiz;
		reporteInorden(actual);

		reporte<<texto;
		reporte<<"}";
		reporte.close();
		system("dot -Tpng RepInorden.dot -o RepInorden.png");
		system("RepInorden.png &");
	}
	
}
Nodo *Arbol::reportePostorden(Nodo *actual){
	if(actual != NULL)
    {
    	if(actual == raiz){
    		reportePostorden(actual->izq);
        	reportePostorden(actual->der);
        	texto = texto + actual->info;
        	
		}else{
			
			reportePostorden(actual->izq);
       		reportePostorden(actual->der);
       	 	texto = texto + actual->info;
        	texto = texto + "->";
        
		}
        
    }
}
void Arbol::reportePostorden(){
	ofstream reporte;
	reporte.open("RepPostorden.dot", ios::out);
	if(reporte.fail()){
		exit(1);
	}else{
		reporte<<"digraph G{\n";
		reporte<<"rankdir = LR;\n";
		reporte<<"node [shape= record];\n";
		Nodo *actual = raiz;
		reportePostorden(actual);
		reporte<<texto;
		reporte<<"}";
		reporte.close();
		system("dot -Tpng RepPostorden.dot -o RepPostorden.png");
		system("RepPostorden.png &");
		
	}
}


