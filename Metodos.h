#ifndef METEODOS_H
#define METODOS_H
#include "json.hpp"
#include "Matriz.h"
#include "Matriz.cpp"
#include "ListaDC.h"
#include "ListaDC.cpp"
#include "ListaD.h"
#include "ListaD.cpp"
#include "Cola.h"
#include "Cola.cpp"
#include "Arbol.h"
#include "Arbol.cpp"
#include "ListaS.h"
#include "ListaS.cpp"
using namespace std;
using json = nlohmann::json;
typedef class Metodos Metodos;

class Metodos
{
	public:
		int dimension;
		Nodo *j1, *j2;
		
		Arbol *usuaios = new Arbol();
		Matriz *matriz = new Matriz();
		
		ListaDC *listaDiccionario = new ListaDC();
		ListaD *fichas = new ListaD();
		ListaD *fichasCopia = new ListaD();
		Cola *fichasDisponibles =new Cola();
		ListaS *scoreboard = new ListaS();
		
		void menu();
		void insertarFichas(ListaDoble *fichas);
		void LecturaDeArchivo(string archivo);
		void ValidarPalabraHorizontal(string palabra, int columnaInicio, int  columnaFinal, int fila, Nodo *jugador);
		void ValidarPalabraVertical(string palabra, int filaInicio, int filaFinal, int columna,Nodo *jugador);
		void RepartirFichas(Nodo *jugador1, Nodo *jugador2);
		
		int PosicionRandom();
		int PuntajeHorizontal(string palabra, int fila);
		int PuntajeVertical(string palabra, int columna);
		
		void reportes(int opcion, Nodo *j1, Nodo *j2);
		void jugar(Nodo *j1, Nodo *j2);
		
		void IngresarJugador();
		void SeleccionarJugador();
		
		bool turno(string palabra,  Nodo *jugador);
		
		void ABC(string palabra, Nodo *Jactual, Nodo *Jsiguiente);
		
		void CambiarFichas(string letras, Nodo *jugador);
	protected:
};

#endif

