#include "Matriz.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

NodoM::Nodo_Matriz(int fila, int columna, char * valor)
{
    this->fila = fila;
    this->columna = columna;
    this->valor = valor;
    this->abajo = NULL;
    this->arriba = NULL;
    this->der = NULL;
    this->izq = NULL;
}

Guia::Guia(int id)
{
    this->id = id;
    this->sig = NULL;
    this->ant = NULL;
    this->entrada = NULL;
}
