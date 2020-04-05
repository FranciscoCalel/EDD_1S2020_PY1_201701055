#include "Matriz.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;  

Nodo_Matriz::Nodo_Matriz(int fila, int columna, char *valor)
{
    this->fila = fila;
    this->columna = columna;
    this->valor = valor;
    this->valorAnt = NULL;
	this->der = NULL;
    this->izq = NULL;
	this->arriba = NULL;
	this->abajo = NULL;
    
    
}

Guia::Guia(int id)
{
    this->id = id;
    this->sig = NULL;
    this->ant = NULL;
    this->entrada = NULL;
}

void Lista_guias::insert(Guia * nuevo)
{
    if(prim == NULL)
    {
       prim = nuevo;
    }
    else
    {
        if(nuevo->id < prim->id) //Inserción al inicio
        {
            nuevo->sig = prim;
            prim->ant = nuevo;
            prim = nuevo;
        }
        else
        {
            Guia * actual = prim;
            while(actual->sig != NULL)
            {
                if(nuevo->id < actual->sig->id) //Inserción en el medio
                {
                    nuevo->sig = actual->sig;
                    actual->sig->ant = nuevo;
                    nuevo->ant = actual;
                    actual->sig = nuevo;
                    break;
                }

                actual = actual->sig;
            }

            if(actual->sig == NULL) //Inserción al final
            {
                actual->sig = nuevo;
                nuevo->ant = actual;
            }
        }
    }
}

Guia * Lista_guias::getGuia(int id)
{
    Guia * actual = prim;
    while(actual != NULL)
    {
        if(actual->id == id)
        {
            return actual;
        }

        actual = actual->sig;
    }

    return NULL;
}

Matriz::Matriz()
{
    this->eFilas = new Lista_guias();       //revisar
    this->eColumnas = new Lista_guias();   //revisar
}

void Matriz::insert(int fila, int columna, char * valor)
{
    Nodo_Matriz * nuevo = new Nodo_Matriz(fila, columna, valor);

    //INSERCION_FILAS
    Guia * eFila = eFilas->getGuia(fila);
    Guia * eColumna = eColumnas->getGuia(columna);
    Nodo_Matriz *aux = buscar(fila, columna);
    if(aux != NULL){
    	aux->valor = valor;
	}else{
		
	
    if(eFila == NULL) //Si no existe encabezado se crea.
    {
        eFila = new Guia(fila);
        eFilas->insert(eFila);
        eFila->entrada = nuevo;
    }
    else
    {
        if(nuevo->columna < eFila->entrada->columna) //Inserción al inicio
        {
            nuevo->der = eFila->entrada;
            eFila->entrada->izq = nuevo;
            eFila->entrada = nuevo;
        }
        else
        {
            Nodo_Matriz * actual = eFila->entrada;
            while(actual->der != NULL)
            {
                if(nuevo->columna < actual->der->columna) //Inserción en el medio
                {
                    nuevo->der = actual->der;
                    actual->der->izq = nuevo;
                    nuevo->izq = actual;
                    actual->der = nuevo;
                    break;
                    
                }

                actual = actual->der;
            }

            if(actual->der == NULL) //Inserción al final
            {
                actual->der = nuevo;
                nuevo->izq = actual;
            }
        }
    }
    //FIN_FILAS

    //INSERCION_COLUMNAS
    
    if(eColumna == NULL) //Si no existe encabezado se crea.
    {
        eColumna = new Guia(columna);
        eColumnas->insert(eColumna);
        eColumna->entrada = nuevo;
    }
    	else
    	{
        	if(nuevo->fila < eColumna->entrada->fila) //Inserción al inicio
        	{
           		nuevo->abajo = eColumna->entrada;
            	eColumna->entrada->arriba = nuevo;
            	eColumna->entrada = nuevo;
        	}
        	else
        	{
            	Nodo_Matriz * actual = eColumna->entrada;
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

void Matriz::recFil()
{
    Guia * eFila = eFilas->prim;
    cout << "Recorrido Por Filas: ";

    while(eFila != NULL)
    {
        Nodo_Matriz * actual = eFila->entrada;
        while(actual != NULL)
        {
        	
            cout << actual->valor;

            if(eFila->sig != NULL || actual->der != NULL)
            {
                cout << "->";
            }


            actual = actual->der;
        }

        eFila = eFila->sig;
    }

    cout << endl;
}

void Matriz::recCol()
{
    Guia * eColumna = eColumnas->prim;
    cout << "Recorrido Por Columnas: ";

    while(eColumna != NULL)
    {
        Nodo_Matriz * actual = eColumna->entrada;
        while(actual != NULL)
        {
            cout << actual->valor;

            if(eColumna->sig != NULL || actual->abajo != NULL)
            {
                cout << "->";
            }

            actual = actual->abajo;
        }

        eColumna = eColumna->sig;
    }

    cout << endl;
}
void Matriz::eliminar(int fila, int columna)
{
	Guia *efila= eFilas->getGuia(fila);
	Guia *ecolumna = eColumnas->getGuia(columna);
	Nodo_Matriz *actual = efila->entrada;
	//eliminar apuntadores accediendo por fila
	if(efila->entrada != 0 ){
		if(actual->columna == ecolumna->entrada->columna){
				if(actual->der !=0){
					actual->der->izq = 0;
					actual->izq = 0;
					efila->entrada = actual->der;
					actual->der = 0;
				}else{
					actual->izq = 0;
					efila->entrada = 0;
					actual->der = 0;
				}
				
		}else{
			
			while(actual->columna!= columna && actual->der != 0){
				actual = actual->der;
			}
			
			if(actual->der != 0){//eliminar en medio
				
				actual->izq->der = actual->der;
		 		actual->der->izq = actual->izq;
			}
			else{//eliminar el ultimo
				
				actual->izq->der = 0;
		 		actual->izq = 0;
			}
		}
	}
	//ELIMINANDO APUNTADORES POR COLUMNA
	
	if(ecolumna->entrada != 0 ){
		
		if(actual->fila == ecolumna->entrada->fila){
			
				if(actual->abajo !=0){
					
					actual->abajo->arriba = 0;
					actual->arriba = 0;
					ecolumna->entrada = actual->abajo;
					actual->abajo = 0;
				}else{
					
					actual->arriba = 0;
					ecolumna->entrada = 0;
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
void Matriz::rep()
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
		Guia * eFila = eFilas->prim;/////***************NOOO TOCAR
		Guia *ecolumna = eColumnas->prim;
		reporte<<"{rank = same;-1,";
		
		while(ecolumna != NULL){
			reporte<<"C";
			reporte<<ecolumna->id;
			if(ecolumna->sig != NULL)
				reporte<<",";
			ecolumna = ecolumna->sig;
			
		}
		ecolumna = eColumnas->prim;
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
			ecolumna = ecolumna->sig;
		}
		ecolumna = eColumnas->prim;
		while(ecolumna != 0){
			reporte<<"C";
			reporte<<ecolumna->id;
			if(ecolumna->sig !=0)
				reporte<<"->";
			ecolumna = ecolumna->sig;
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
			eFila = eFila->sig;
		}
		eFila = eFilas->prim;
		while(eFila != 0){
			reporte<<"F";
			reporte<<eFila->id;
			
			if(eFila->sig !=0)
				reporte<<"->";
			eFila = eFila->sig;
			
		}
		reporte<<"\n";
		eFila = eFilas->prim;
		while(eFila != NULL){
			Nodo_Matriz *actual=eFila->entrada;
			while(actual != NULL){
				reporte<<actual->fila;
				reporte<<actual->columna;
				reporte<<"[label=\"";
				reporte<<actual->valor;
				reporte<<"\"];\n";
				actual = actual->der;
			}
			
			eFila = eFila->sig;
		}
		eFila = eFilas->prim;
		while(eFila != NULL){
			Nodo_Matriz *actual = eFila->entrada;
			reporte<<"F";
			reporte<<eFila->id;
			
			reporte<<"->";
			reporte<<actual->fila;
			reporte<<actual->columna;
			reporte<<"\n";
			eFila = eFila->sig;
		}
		///***********apuntadores de cabeceras columnas a NodoMs
		ecolumna = eColumnas->prim;
		while(ecolumna!=NULL){
			Nodo_Matriz *actual = ecolumna->entrada;
			while(actual!=NULL){
				reporte<<actual->fila;
				reporte<<actual->columna;
				reporte<<"[label=\"";
				reporte<<actual->valor;
				reporte<<"\"];\n";
				actual = actual->abajo;
			}
			
			ecolumna = ecolumna->sig;
		}
		ecolumna = eColumnas->prim;
		while(ecolumna != NULL){
			Nodo_Matriz *actual = ecolumna->entrada;
			reporte<<"C";
			
			reporte<<ecolumna->id;
			reporte<<"->";
			reporte<<actual->fila;
			reporte<<actual->columna;
			
			reporte<<"\n";
			ecolumna = ecolumna->sig;
		}
		eFila =eFilas->prim;
    	while(eFila != NULL){
    		Nodo_Matriz *actual = eFila->entrada;
    		reporte<<"{rank = same;";
    		reporte<<"F";
    		reporte<<eFila->id;
    		
    		reporte<<",";
    		while(actual != NULL){
    			reporte<<actual->fila;
    			reporte<<actual->columna;
    			if(eFila->sig != NULL || actual->der != NULL){
    				if(actual->der !=NULL){
    					reporte<<",";
					}
    				
				}
				actual = actual->der;
			}
			
			eFila = eFila->sig;
			reporte<<"};\n";
			
		}
		//COLUMNAS
		ecolumna = eColumnas->prim;
		
		while(ecolumna != NULL){
    		Nodo_Matriz *actual = ecolumna->entrada;
    		reporte<<"{rank = main;";
    		reporte<<"C";
    		reporte<<ecolumna->id;
			
			reporte<<",";
    		while(actual != NULL){
    			
    			reporte<<actual->fila;
    			reporte<<actual->columna;
    			if(ecolumna->sig != NULL || actual->abajo != NULL){
    				if(actual->abajo !=NULL){
    					reporte<<",";
					}
    				
				}
				actual = actual->abajo;
			}
			ecolumna = ecolumna->sig;
			reporte<<"};\n";
		}
		//a->b punteros siguientes filas
		eFila = eFilas->prim;
		while(eFila != NULL){
			Nodo_Matriz * actual = eFila->entrada;
	        while(actual != NULL)
	        {
	            reporte<< actual->fila;
	            reporte<<actual->columna;
	
	            if(eFila->sig != NULL || actual->der != NULL)
	            {
	                if(actual->der != NULL)
						reporte<< "->";
	            }
	            actual = actual->der;
	        }
	       	reporte<<"\n";
	        actual = eFila->entrada;
	        
	        //pintar punteros anteriores filas
	        reporte<<actual->fila;
	        reporte<<actual->columna;
	        
	        reporte<<"->";
	        reporte<<"F";
	        reporte<<eFila->id;
	        
	        reporte<<"\n";
	        while(actual != NULL){
	        	
	        	if(actual->der != NULL){
	        		reporte<<actual->der->fila;
	        		reporte<<actual->der->columna;
	        		
	        		reporte<<"->";
	        		reporte<<actual->fila;
	        		reporte<<actual->columna;
	        		
	        		reporte<<"\n";
	        		actual = actual->der;
	        		
				}else{
					
					actual = actual->der;
				}
	        		
			}
	
	        eFila = eFila->sig;
	        reporte<<"\n";
	    }
	    //punteros abajo columnass
	    ecolumna = eColumnas->prim;
	    while(ecolumna != NULL){
	    	Nodo_Matriz *actual = ecolumna->entrada;
	    	reporte<<actual->fila;
	        reporte<<actual->columna;
	    	
	    	reporte<<"->";
	    	reporte<<"C";
	    	reporte<<ecolumna->id;
	    	reporte<<"\n";
	    	while(actual != NULL){
	    		reporte<<actual->fila;
	        	reporte<<actual->columna;
	    		
	    		if(ecolumna->sig != NULL || actual->abajo != NULL){
	    			if(actual->abajo != NULL)
						reporte<<"->";
				}
				actual = actual->abajo;
			}
			actual = ecolumna->entrada;
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
			ecolumna = ecolumna->sig;
			reporte<<"\n";
		}
	    reporte<<"\n";
	    reporte<<"}";
	    reporte.close();
	    system("dot -Tpng RepMatriz.dot -o RepMatriz.png");
		system("RepMatriz.png &");
	}	
}

Nodo_Matriz  * Matriz::buscar(int fila, int columna){
	Guia *efila = eFilas->prim;
	if(efila!=NULL){
			while(efila->id != fila && efila->sig != NULL){
			efila = efila->sig;
		}
		Nodo_Matriz * actual = efila->entrada;
		while(actual->columna != columna && actual->der!= NULL){
			actual = actual->der;
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
