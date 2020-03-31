#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H
#include <iostream>
//#include <fstream>
#include  <string.h>
using namespace std;
typedef class nodoldc nodoldc;
typedef class ListaDC ListaDC;
class nodoldc
{
	public: 
		string palabra;
		nodoldc *sig;
		nodoldc *ant;
		nodoldc(string palabra);

	
};
class ListaDC
{
	public:
		nodoldc *ultimo;
		nodoldc *primero;
		int tamaLC;
		ListaDC();
		void insertar(string palabra);
		void print();
		void reporte();
	protected:
};

#endif
