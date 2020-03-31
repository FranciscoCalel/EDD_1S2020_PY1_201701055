#ifndef LISTAS_H
#define LISTAS_H

typedef class nodoLS nodoLS;
typedef class ListaS ListaS;

class nodoLS
{
	public:
	char *nombre;
	int punteo;
	nodoLS *sig;
	nodoLS(char * nombre, int punteo);
};
class ListaS
{
	public:
		nodoLS *primero;
		int tamLS;
		
		ListaS();
		void insertarOrdenada(char *nombre, int punteo);
		void print();
		void reporte();
		void reporteJugador(char *nombre);
	protected:
};

#endif

