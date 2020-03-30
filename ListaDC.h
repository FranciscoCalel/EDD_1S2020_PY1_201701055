#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H
#include <iostream>
//#include <fstream>
#include  <string.h>
using namespace std;
typedef class nodold nodold;
typedef class ListaDC ListaDC;
class nodold
{
	public: 
		string palabra;
		nodold *sig;
		nodold *ant;
		nodold(string palabra);

	
};
class ListaDC
{
	public:
		nodold *ultimo;
		nodold *primero;
		int tamaLC;
		ListaDC();
		void insertar(string palabra);
		void print();
		void reporte();
	protected:
};

#endif
