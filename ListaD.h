#ifndef LISTAD_H
#define LISTAD_H
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

typedef class NodoLD NodoLD;
typedef class ListaD ListaD;
class NodoLD{
	public:
	char *letra;
	NodoLD* sig;
	NodoLD* ant;
	int cant;
	int punteo;
	NodoLD(char *letra, int cant, int punteo);
};
class ListaD
{
	public:
		NodoLD* ultimo;
		NodoLD* primero;
		int tamLD;
		int rep;
		ListaD();
		void insertar(char *letra, int cant, int punteo);
		void eliminarCantidad(char *letra, int cant);
		void print();
		void reporte();
		NodoLD* buscar(char * letra);
	protected:
};

#endif

