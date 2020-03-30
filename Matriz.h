#ifndef MATRIZ_H
#define MATRIZ_H

typedef class NodoM NodoM;
typedef class Encabezado Encabezado;
typedef class ListaEncabezados ListaEncabezados;
typedef class Matriz Matriz;

class Nodo_Matriz
{
	public:
	int fila, columna;
	char *valorAnt;
	char * valor;	
	NodoMatriz *izq;
	NodoMatriz *der;
	NodoMatriz *arriba;
	NodoMatriz *abajo;
	NodoMatriz(int fila, int columna, char*valor);		
};

class Guia{

	public:
		int id;
		Guia * sig;
		Guia * ant;
		NodoMatriz * entrada;
		Guia(int id);
};

class Lista_guias{
	Guia * prim;
	void insert(Guia * nuevo);
	Guia * getGuia(int id);
};

class Matriz{
	Lista_Guias * Nfilas;
	Lista_Guias * NColumnas;
	Matriz();
	void insertar(int fil, int columna, char * valor);
	void recFil();
	void recCol();
	void eliminar(int fila, int columna)
	void rep();
	NodoMatriz * buscar(int fila,int columna);	
};

#endif // MATRIZORTOGONAL
