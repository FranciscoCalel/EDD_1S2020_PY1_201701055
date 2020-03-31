#ifndef MATRIZ_H
#define MATRIZ_H

typedef class Nodo_Matriz Nodo_Matriz;
typedef class Guia Guia;
typedef class Lista_guias Lista_guias;
typedef class Matriz Matriz;

class Nodo_Matriz
{
	public:
	int fila, columna;
	char *valorAnt;
	char * valor;	
	Nodo_Matriz *izq;
	Nodo_Matriz *der;
	Nodo_Matriz *arriba;
	Nodo_Matriz *abajo;
	Nodo_Matriz(int fila, int columna, char*valor);		
};

class Guia{

	public:
		int id;
		Guia * sig;
		Guia * ant;
		Nodo_Matriz * entrada;
		Guia(int id);
};

class Lista_guias{
	public:
	Guia * prim;
	void insert(Guia * nuevo);
	Guia * getGuia(int id);
};

class Matriz{
	public:
	Lista_guias * eFilas;
	Lista_guias * eColumnas;
	Matriz();
	void insert(int fila, int columna, char * valor);
	void recFil();
	void recCol();
	void eliminar(int fila, int columna);
	void rep();
	Nodo_Matriz * buscar(int fila,int columna);	
};

#endif // MATRIZORTOGONAL

