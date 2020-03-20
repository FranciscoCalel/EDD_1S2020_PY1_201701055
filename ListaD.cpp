#include "ListaD.h"

using namespace std;

NodoLD::NodoLD(char*letra, int cantidad, int puntaje){
	this->letra = letra;
	this->cantidad = cantidad;
	this->punteo = punteo;
	this->sig = 0;
	this->ant = 0;
}
ListaD::ListaD(){
	this->primero = 0;
	this->tamLD=-1;
	
}
void ListaD::insertar(char *letra, int cantidad, int punteo){
	NodoLD *nuevo = new NodoLD(letra, cantidad,punteo);
	if(tamLD == -1){
		primero = nuevo;
		tamLD = 0;
	}
	else{
		NodoLD*aux = primero;
		bool band = false;
		while(aux->sig != NULL){
			if(aux->letra == letra){
				aux->cantidad ++;
				aux = aux->sig;
				band = true;
			}else{
				aux = aux->sig;
			}
		}
		if(aux->letra != letra && band == false){
			aux->sig = nuevo;
			nuevo->ant = aux;
			aux = nuevo;
			
			tamLD++;
		}else if (band==false){
			
			aux->cantidad = aux->cantidad+1;
		}
	}
}
void ListaD::print(){
	if(tamLD == -1){
		cout<<"Lista Vacía";
	}else{
		NodoLD * aux = primero;
		while(aux->sig != 0){
			cout<<aux->letra;
			cout<<aux->cantidad;
			cout<<"\n";
			aux = aux->sig;
		}
		cout<<aux->letra;
		cout<<aux->cantidad;
		cout<<"\n";
	}
}
void ListaD::eliminarCantidad(char*letra, int cant){
	NodoLD *aux= primero;
	if(aux->sig != 0){
		
		while(aux->sig != 0){
			if(aux->letra == letra){
				aux->cantidad = aux->cantidad-cant;
				if(aux->cantidad ==0){
					if(aux == primero){
						aux->sig->ant = 0;
						primero = aux->sig;
						aux->sig = 0;
						tamLD=tamLD-cant;
						
					}
					else{
						aux->ant->sig = aux->sig;
						aux->sig->ant = aux->ant;
						tamLD=tamLD-cant;
					}
					break;
				}
				break;
				
			}else{
				aux = aux->sig;
			}
		}
		
	
	
	}
	if(aux->letra == letra && aux->sig == 0){
		aux->cantidad = aux->cantidad-cant;
		if(aux->cantidad ==0){
			if(aux == primero){
				//aux->sig->ant = 0;
				primero = aux->sig;
				aux->sig = 0;
				tamLD=tamLD-cant;
				
			}
			else{
				aux->ant->sig = 0;
				tamLD=tamLD-cant;
			}
		}
	}
	
	
}

void ListaD::reporte(){
		ofstream reporte;
		reporte.open("RepFichas.dot", ios::out);
		if (reporte.fail()) {
			cout << "Reporte no creado" << endl;
			exit(1);
		}
		else {
			reporte << "digraph G{\n";
			reporte << "rankdir = LR;\n";
			reporte << "node[shape = record]; \n";
			NodoLD* aux = primero;
			
				while(aux->sig != 0){
					reporte<<aux->letra;
					reporte<<aux->cantidad;
					reporte<<"->";
					reporte<<aux->sig->letra;
					reporte<<aux->sig->cantidad;
					reporte<<"\n";
					aux = aux->sig;
				}
				while(aux->ant != 0){
					reporte<<aux->letra;
					reporte<<aux->cantidad;
					reporte<<"->";
					reporte<<aux->ant->letra;
					reporte<<aux->ant->cantidad;
					reporte<<"\n";
					aux = aux->ant;
					
				}
			reporte << "}";
			
		}
		reporte.close();
		system("dot -Tpng RepFichas.dot -o RepFichas.png");
		system("RepFichaspng &");
	
}
NodoLD* ListaD::buscar(char* letra){
	
	NodoLD *aux= primero;
	while(aux->sig != 0){
		if(aux->letra != letra )
			aux = aux->sig;
		else
			return aux;
	}
	if(aux->letra == letra){
		return aux;
	}else{
		return NULL;	
	}
	
}



