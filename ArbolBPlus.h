#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "VideoJuego.h"
using namespace std;

struct NodoBPlus {
	bool hoja; // dice si es hoja o no
	vector <VideoJuego> videojuegos; // vector de claves
	vector <NodoBPlus*> hijos; // vector de punteros a hijos
	NodoBPlus* siguiente; // puntero al siguiente nodo hoja
	NodoBPlus(bool esHoja);
};

class ArbolBPlus {
private:
	NodoBPlus* raiz; // puntero a la raiz del arbol 
	void dividirHoja(NodoBPlus* nodo, stack<NodoBPlus*>&pila); //metodo para dividir hoja
	void insertarEnPadre(NodoBPlus* hojaIzq, NodoBPlus* hojaDer, string nodoInterno, stack<NodoBPlus*>& pila);//metodo par insertar en el padre datos del nodo izq y der
	void dividirNodoInterno(NodoBPlus* nodo, stack<NodoBPlus*>& pila); //metodo para dividir nodo interno
public:
	ArbolBPlus();
	VideoJuego* buscar(string nombre);
	void imprimir();
	void insertar(VideoJuego videojuego); //insertar una nueva clave (videojuego)
};