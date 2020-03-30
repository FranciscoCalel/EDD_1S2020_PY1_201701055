#include "Matriz.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

NodoM::Nodo_M(int fila, int columna, char * valor)
{
    this->fila = fila;
    this->columna = columna;
    this->valor = valor;
    this->abajo = NULL;
    this->arriba = NULL;
    this->der = NULL;
    this->izq = NULL;
    this->valorAnt = NULL;
}

Guia::Guia(int id)
{
    this->id = id;
    this->sig = NULL;
    this->ant = NULL;
    this->entrada = NULL;
}

void Lista_guias::insertar(Guia * nuevo)
{
    if(primero == NULL)
    {
       primero = nuevo;
    }
    else
    {
        if(nuevo->id < primero->id) //Inserción al inicio
        {
            nuevo->siguiente = primero;
            primero->anterior = nuevo;
            primero = nuevo;
        }
        else
        {
            Guia * actual = primero;
            while(actual->siguiente != NULL)
            {
                if(nuevo->id < actual->siguiente->id) //Inserción en el medio
                {
                    nuevo->siguiente = actual->siguiente;
                    actual->siguiente->anterior = nuevo;
                    nuevo->anterior = actual;
                    actual->siguiente = nuevo;
                    break;
                }

                actual = actual->siguiente;
            }

            if(actual->siguiente == NULL) //Inserción al final
            {
                actual->siguiente = nuevo;
                nuevo->anterior = actual;
            }
        }
    }
}

Guia * Lista_guias::getGuia(int id)
{
    Guia * actual = primero;
    while(actual != NULL)
    {
        if(actual->id == id)
        {
            return actual;
        }

        actual = actual->siguiente;
    }

    return NULL;
}

Matriz::Matriz()
{
    this->eFilas = new Lista_guias();
    this->eColumnas = new Lista_guias();
}

void Matriz::insertar(int fila, int columna, char * valor)
{
    NodoM * nuevo = new NodoM(fila, columna, valor);

    //INSERCION_FILAS
    Guia * eFila = eFilas->getGuia(fila);
    Guia * eColumna = eColumnas->getGuia(columna);
    NodoM *aux = buscar(fila, columna);
    if(aux != NULL){
    	aux->valor = valor;
	}else{
		
	
    if(eFila == NULL) //Si no existe encabezado se crea.
    {
        eFila = new Encabezado(fila);
        eFilas->insertar(eFila);
        eFila->acceso = nuevo;
    }
    else
    {
        if(nuevo->columna < eFila->acceso->columna) //Inserción al inicio
        {
            nuevo->derecha = eFila->acceso;
            eFila->acceso->izquierda = nuevo;
            eFila->acceso = nuevo;
        }
        else
        {
            NodoM * actual = eFila->acceso;
            while(actual->derecha != NULL)
            {
                if(nuevo->columna < actual->derecha->columna) //Inserción en el medio
                {
                    nuevo->derecha = actual->derecha;
                    actual->derecha->izquierda = nuevo;
                    nuevo->izquierda = actual;
                    actual->derecha = nuevo;
                    break;
                    
                }

                actual = actual->derecha;
            }

            if(actual->derecha == NULL) //Inserción al final
            {
                actual->derecha = nuevo;
                nuevo->izquierda = actual;
            }
        }
    }
    //FIN_FILAS

    //INSERCION_COLUMNAS
    
    if(eColumna == NULL) //Si no existe encabezado se crea.
    {
        eColumna = new Guia(columna);
        eColumnas->insertar(eColumna);
        eColumna->acceso = nuevo;
    }
    else
    {
        if(nuevo->fila < eColumna->acceso->fila) //Inserción al inicio
        {
            nuevo->abajo = eColumna->acceso;
            eColumna->acceso->arriba = nuevo;
            eColumna->acceso = nuevo;
        }
        else
        {
            NodoM * actual = eColumna->acceso;
            while(actual->abajo != NULL)
            {
                if(nuevo->fila < actual->abajo->fila) //Inserción en el medio
                {
                    nuevo->abajo = actual->abajo;
                    actual->abajo->arriba = nuevo;
                    nuevo->arriba = actual;
                    actual->abajo = nuevo;
                    break;
                }

                actual = actual->abajo;
            }

            if(actual->abajo == NULL) //Inserción al final
            {
                actual->abajo = nuevo;
                nuevo->arriba = actual;
            }
        }
    }
    //FIN_COLUMNAS
}
}

void Matriz::recorrerFilas()
{
    Guia * eFila = eFilas->primero;
    cout << "Recorrido Por Filas: ";

    while(eFila != NULL)
    {
        NodoM * actual = eFila->acceso;
        while(actual != NULL)
        {
        	
            cout << actual->valor;

            if(eFila->siguiente != NULL || actual->derecha != NULL)
            {
                cout << "->";
            }


            actual = actual->derecha;
        }

        eFila = eFila->siguiente;
    }

    cout << endl;
}

void Matriz::recorrerColumnas()
{
    Guia * eColumna = eColumnas->primero;
    cout << "Recorrido Por Columnas: ";

    while(eColumna != NULL)
    {
        NodoM * actual = eColumna->acceso;
        while(actual != NULL)
        {
            cout << actual->valor;

            if(eColumna->siguiente != NULL || actual->abajo != NULL)
            {
                cout << "->";
            }

            actual = actual->abajo;
        }

        eColumna = eColumna->siguiente;
    }

    cout << endl;
}
void Matriz::eliminar(int fila, int columna)
{
	Guia *efila= eFilas->getGuia(fila);
	Guia *ecolumna = eColumnas->getGuia(columna);
	NodoM *actual = efila->acceso;
	//eliminar apuntadores accediendo por fila
	if(efila->acceso != 0 ){
		if(actual->columna == ecolumna->acceso->columna){
				if(actual->derecha !=0){
					actual->derecha->izquierda = 0;
					actual->izquierda = 0;
					efila->acceso = actual->derecha;
					actual->derecha = 0;
				}else{
					actual->izquierda = 0;
					efila->acceso = 0;
					actual->derecha = 0;
				}
				
		}else{
			
			while(actual->columna!= columna && actual->derecha != 0){
				actual = actual->derecha;
			}
			
			if(actual->derecha != 0){//eliminar en medio
				
				actual->izquierda->derecha = actual->derecha;
		 		actual->derecha->izquierda = actual->izquierda;
			}
			else{//eliminar el ultimo
				
				actual->izquierda->derecha = 0;
		 		actual->izquierda = 0;
			}
		}
	}
	//ELIMINANDO APUNTADORES POR COLUMNA
	
	if(ecolumna->acceso != 0 ){
		
		if(actual->fila == ecolumna->acceso->fila){
			
				if(actual->abajo !=0){
					
					actual->abajo->arriba = 0;
					actual->arriba = 0;
					ecolumna->acceso = actual->abajo;
					actual->abajo = 0;
				}else{
					
					actual->arriba = 0;
					ecolumna->acceso = 0;
					actual->abajo = 0;
				}
				
		}else{
			
			while(actual->fila!= fila && actual->abajo != 0){
				actual = actual->abajo;
			}
			
			if(actual->abajo != 0){//eliminar en medio
				
				actual->arriba->abajo = actual->abajo;
		 		actual->abajo->arriba = actual->arriba;
			}
			else{//eliminar el ultimo
				
				actual->arriba->abajo = 0;
		 		actual->arriba = 0;
			}
		}
	}
}
void Matriz::reporte()
{
	ofstream reporte;
	reporte.open("RepMatriz.dot", ios::out);
	if(reporte.fail()){
		exit(1);
	}
	
	else{
		reporte<<"digraph G {\n";
		reporte<<"node[shape=box, style=filled, color = Gray80];\n";
		reporte<<"edge[color=black]\n";
		reporte<<"rankdir=UD\n";
		Guia * eFila = eFilas->primero;/////***************NOOO TOCAR
		Guia *ecolumna = eColumnas->primero;
		reporte<<"{rank = same;-1,";
		
		while(ecolumna != NULL){
			reporte<<"C";
			reporte<<ecolumna->id;
			if(ecolumna->siguiente != NULL)
				reporte<<",";
			ecolumna = ecolumna->siguiente;
			
		}
		ecolumna = eColumnas->primero;
		reporte<<"};\n";
		reporte<<"-1[label=\"RAIZ\"];\n";
		reporte<<"-1->";
		reporte<<"C";
		reporte<<ecolumna->id;
		
		reporte<<"\n";
		while(ecolumna!=0){
			reporte<<"C";
			reporte<<ecolumna->id;
			reporte<<"[label=\"";
			reporte<<ecolumna->id;
			reporte<<"\"];\n";
			ecolumna = ecolumna->siguiente;
		}
		ecolumna = eColumnas->primero;
		while(ecolumna != 0){
			reporte<<"C";
			reporte<<ecolumna->id;
			if(ecolumna->siguiente !=0)
				reporte<<"->";
			ecolumna = ecolumna->siguiente;
		}
		reporte<<"\n";
		////****************** apuntaddores de cabeceras filas a NodoMs
		reporte<<"-1->";
		reporte<<"F";
		reporte<<eFila->id;
		
		reporte<<"\n";
		while(eFila != 0){
			reporte<<"F";
			reporte<<eFila->id;
			
			reporte<<"[label=\"";
			reporte<<eFila->id;
			reporte<<"\"];\n";
			eFila = eFila->siguiente;
		}
		eFila = eFilas->primero;
		while(eFila != 0){
			reporte<<"F";
			reporte<<eFila->id;
			
			if(eFila->siguiente !=0)
				reporte<<"->";
			eFila = eFila->siguiente;
			
		}
		reporte<<"\n";
		eFila = eFilas->primero;
		while(eFila != NULL){
			NodoM *actual=eFila->acceso;
			while(actual != NULL){
				reporte<<actual->fila;
				reporte<<actual->columna;
				reporte<<"[label=\"";
				reporte<<actual->valor;
				reporte<<"\"];\n";
				actual = actual->derecha;
			}
			
			eFila = eFila->siguiente;
		}
		eFila = eFilas->primero;
		while(eFila != NULL){
			NodoM *actual = eFila->acceso;
			reporte<<"F";
			reporte<<eFila->id;
			
			reporte<<"->";
			reporte<<actual->fila;
			reporte<<actual->columna;
			reporte<<"\n";
			eFila = eFila->siguiente;
		}
		///***********apuntadores de cabeceras columnas a NodoMs
		ecolumna = eColumnas->primero;
		while(ecolumna!=NULL){
			NodoM *actual = ecolumna->acceso;
			while(actual!=NULL){
				reporte<<actual->fila;
				reporte<<actual->columna;
				reporte<<"[label=\"";
				reporte<<actual->valor;
				reporte<<"\"];\n";
				actual = actual->abajo;
			}
			
			ecolumna = ecolumna->siguiente;
		}
		ecolumna = eColumnas->primero;
		while(ecolumna != NULL){
			NodoM *actual = ecolumna->acceso;
			reporte<<"C";
			
			reporte<<ecolumna->id;
			reporte<<"->";
			reporte<<actual->fila;
			reporte<<actual->columna;
			
			reporte<<"\n";
			ecolumna = ecolumna->siguiente;
		}
		eFila =eFilas->primero;
    	while(eFila != NULL){
    		NodoM *actual = eFila->acceso;
    		reporte<<"{rank = same;";
    		reporte<<"F";
    		reporte<<eFila->id;
    		
    		reporte<<",";
    		while(actual != NULL){
    			reporte<<actual->fila;
    			reporte<<actual->columna;
    			if(eFila->siguiente != NULL || actual->derecha != NULL){
    				if(actual->derecha !=NULL){
    					reporte<<",";
					}
    				
				}
				actual = actual->derecha;
			}
			
			eFila = eFila->siguiente;
			reporte<<"};\n";
			
		}
		//COLUMNAS
		ecolumna = eColumnas->primero;
		
		while(ecolumna != NULL){
    		NodoM *actual = ecolumna->acceso;
    		reporte<<"{rank = main;";
    		reporte<<"C";
    		reporte<<ecolumna->id;
			
			reporte<<",";
    		while(actual != NULL){
    			
    			reporte<<actual->fila;
    			reporte<<actual->columna;
    			if(ecolumna->siguiente != NULL || actual->abajo != NULL){
    				if(actual->abajo !=NULL){
    					reporte<<",";
					}
    				
				}
				actual = actual->abajo;
			}
			ecolumna = ecolumna->siguiente;
			reporte<<"};\n";
		}
		//a->b punteros siguientes filas
		eFila = eFilas->primero;
		while(eFila != NULL){
			NodoM * actual = eFila->acceso;
	        while(actual != NULL)
	        {
	            reporte<< actual->fila;
	            reporte<<actual->columna;
	
	            if(eFila->siguiente != NULL || actual->derecha != NULL)
	            {
	                if(actual->derecha != NULL)
						reporte<< "->";
	            }
	            actual = actual->derecha;
	        }
	       	reporte<<"\n";
	        actual = eFila->acceso;
	        
	        //pintar punteros anteriores filas
	        reporte<<actual->fila;
	        reporte<<actual->columna;
	        
	        reporte<<"->";
	        reporte<<"F";
	        reporte<<eFila->id;
	        
	        reporte<<"\n";
	        while(actual != NULL){
	        	
	        	if(actual->derecha != NULL){
	        		reporte<<actual->derecha->fila;
	        		reporte<<actual->derecha->columna;
	        		
	        		reporte<<"->";
	        		reporte<<actual->fila;
	        		reporte<<actual->columna;
	        		
	        		reporte<<"\n";
	        		actual = actual->derecha;
	        		
				}else{
					
					actual = actual->derecha;
				}
	        		
			}
	
	        eFila = eFila->siguiente;
	        reporte<<"\n";
	    }
	    //punteros abajo columnass
	    ecolumna = eColumnas->primero;
	    while(ecolumna != NULL){
	    	NodoM *actual = ecolumna->acceso;
	    	reporte<<actual->fila;
	        reporte<<actual->columna;
	    	
	    	reporte<<"->";
	    	reporte<<"C";
	    	reporte<<ecolumna->id;
	    	reporte<<"\n";
	    	while(actual != NULL){
	    		reporte<<actual->fila;
	        	reporte<<actual->columna;
	    		
	    		if(ecolumna->siguiente != NULL || actual->abajo != NULL){
	    			if(actual->abajo != NULL)
						reporte<<"->";
				}
				actual = actual->abajo;
			}
			actual = ecolumna->acceso;
			reporte<<"\n";
	        
	        //pintar punteros anteriores columnas
	       while(actual != NULL){
	        	
	        	if(actual->abajo != NULL){
	        		reporte<<actual->abajo->fila;
	        		reporte<<actual->abajo->columna;
	        		
	        		reporte<<"->";
	        		reporte<<actual->fila;
	        		reporte<<actual->columna;
	        		reporte<<"\n";
	        		actual = actual->abajo;
	        		
				}else{
					
					actual = actual->abajo;
				}
	        		
			}
			ecolumna = ecolumna->siguiente;
			reporte<<"\n";
		}
	    reporte<<"\n";
	    reporte<<"}";
	    reporte.close();
	    system("dot -Tpng RepMatriz.dot -o RepMatriz.png");
		system("RepMatriz.png &");
	}	
}

NodoM  * Matriz::buscar(int fila, int columna){
	Guia *efila = eFilas->primero;
	if(efila!=NULL){
			while(efila->id != fila && efila->siguiente != NULL){
			efila = efila->siguiente;
		}
		NodoM * actual = efila->acceso;
		while(actual->columna != columna && actual->derecha!= NULL){
			actual = actual->derecha;
		}
		if(actual != NULL && actual->columna == columna){
				//cout<<"VALOR ENCONTRADO: ";
			//cout<<actual->valor;
			//cout<<"\n";
			return actual;
		}
		else{
			//cout<<"VALOR NO ENCONTRADO";
			return NULL;
		}
	}else{
		return NULL;
	}
	
}
