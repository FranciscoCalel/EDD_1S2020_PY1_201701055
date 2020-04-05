#include <iostream>
#include<string>
#include "Metodos.h"
#include "Metodos.cpp"
#include<conio.h>
using namespace std;

/* create franc */
int main(int argc, char** argv) {
	Metodos *met= new Metodos();
	met->menu();
	
	
	return 0;
}
