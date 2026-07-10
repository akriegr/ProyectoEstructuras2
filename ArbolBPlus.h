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
	void destruirNodo(NodoBPlus* nodo); //metodo recursivo para destruir nodo
	bool eliminarDeHoja(NodoBPlus* hoja, string nombre); //metodo recursivo para eliminar clave
	void prestarIzquierda(NodoBPlus* nodo, int posicion); //metodo para prestar clave del hijo izquierdo
	void prestarDerecha(NodoBPlus* nodo, int posicion); //metodo para prestar clave del hijo derecho
	void fusionar(NodoBPlus* nodo, int posicion); //metodo para fusionar nodos

public:
	ArbolBPlus(); //constructor
	~ArbolBPlus();//destructor
	VideoJuego* buscar(string nombre);
	void imprimir();
	void vaciarArbol();//metodo para vaciar el arbol
	void destruirArbol();//metodo para destruir el arbol
	void insertarVideoJuego(VideoJuego videojuego); //insertar una nueva clave (videojuego)
	bool actualizarVideoJuego(string nombre, string nuevoNombre); //actualizar un videojuego existente
	bool eliminarVideoJuego(string nombre); //eliminar un videojuego existente)
};