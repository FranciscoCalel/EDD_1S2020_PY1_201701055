#ifndef COLA_H
#define COLA_H
typedef class nodoCola nodoCola;
typedef class Cola Cola;

class nodoCola
{
	public:
		char *letra;
		int punteo;
		nodoCola *sig;
		nodoCola(char *letra, int punteo);
	
	
};
class Cola
{
	public:
		nodoCola * primero;
		nodoCola *ultimo;
		int tamCola;
		Cola();
		void insertar(char *letra, int punteo);
		void eliminar();
		void reporte();
		void print();
	protected:
};

#endif
