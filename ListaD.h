#ifndef LISTAD_H
#define LISTAD_H
#include <fstream>
#include <string.h>
#include <iostream>

using namespace std;


typedef class NodoLD NodoLD;
typedef class ListaD ListaD;
class NodoLD{
	public:
	char *letra;
	NodoLD* sig;
	NodoLD* ant;
	int cantidad;
	int puntaje;
	NodoLD(char *letra, int cant, int puntaje);
};

class ListaD
{
	public:
		NodoLD* ultimo;
		NodoLD* primero;
		int tamLD;
		int rep;
		ListaD();
		void insertar(char *letra, int cantidad, int puntaje);
		void eliminarCantidad(char *letra, int cant);
		void print();
		void reporte();
		NodoLD* buscar(char * letra);
	protected:
};

#endif

