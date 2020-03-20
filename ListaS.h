#ifndef LISTAS_H
#define LISTAS_H

typedef class nodoLS nodoLS;
typedef class ListaS ListaS;

class nodoLS
{
	public:
	
	char *nombre;
	int puntos;
	
	nodoLS *sig;
	nodoLS(char * nombre, int puntos);
};
class LS
{
	public:
		nodoLS *primero;
		int tamLS;
		
		ListaS();
		void insertarOrdenada(char *nombre, int puntos);
		
		void print();
		void reporte();
		
		void reporteJugador(char *nombre);
	protected:
};

#endif
