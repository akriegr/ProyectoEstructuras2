#include <iostream>
#include "ArbolBPLus.h"
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

NodoBPlus::NodoBPlus(bool esHoja) {
	hoja = esHoja; //reviso si es hoja o no
	siguiente = nullptr; // puntero al siguiente nodo hoja
}

ArbolBPlus::ArbolBPlus() {
	raiz = new NodoBPlus(true); //inicializo la raiz como un nodo hoja
}
void ArbolBPlus::insertar(VideoJuego videojuego) {
	//Si la raiz esta vacia
	if (raiz->videojuegos.empty()){
		raiz->videojuegos.push_back(videojuego);
		return;
	}

	//empiezo buscando la hoja donde inserta la clave y guardo el cambio 
	stack<NodoBPlus*> pila;
	NodoBPlus* nodoActual = raiz; //empiezo en la raiz

	while(!nodoActual->hoja)//mientras el nodo no sea un hoja sigo bajando
	{
		pila.push(nodoActual); //guardo el nodo actual en la pila
		
		//encuentro la posicion donde va la clave
		int posicion = 0;
		while (posicion < nodoActual->videojuegos.size() && videojuego.getNombre() > nodoActual->videojuegos[posicion].getNombre()) {
			posicion++;
		}
		nodoActual = nodoActual->hijos[posicion]; //bajo al hijo correspondiente
	}
	NodoBPlus* hoja = nodoActual; //guardo el nodo hoja donde se va a insertar la clave
	auto posicionInsertar = lower_bound(hoja->videojuegos.begin(), hoja->videojuegos.end(), videojuego, [](const VideoJuego& a, const VideoJuego& b) {
		return a.getNombre() < b.getNombre();
		});

	hoja->videojuegos.insert(posicionInsertar, videojuego); //inserto el videojuego en la hoja

	//reviso si la hoja necesita dividirse, uso orden de 4
	if (hoja->videojuegos.size() <= 4) {
		return; // si hay espacio solo hago return
	}

	dividirHoja(hoja, pila); //si no hay espacio divido la hoja)
}
void ArbolBPlus::dividirHoja(NodoBPlus* hoja, stack<NodoBPlus*>&pila) {
	//creo una nueva hoja 

	NodoBPlus* nuevaHoja = new NodoBPlus(true);

	//calculo donde divido el nodo
	int mitad = hoja->videojuegos.size() / 2;

	//copio la mitad derecha a la nueva hoja

	nuevaHoja->videojuegos.assign(hoja->videojuegos.begin() + mitad, hoja->videojuegos.end());

	//redimensiono la hoja original paar que solo guarde la mitad izquierda 
	hoja->videojuegos.resize(mitad);

	//actualizar punteros siguientes 
	nuevaHoja->siguiente = hoja->siguiente;
	hoja->siguiente = nuevaHoja;

	//clave que sube al padre es 1er elemento de la nueva hoja 
	//Verifico que la nueva hoja no este vacia
	if (nuevaHoja->videojuegos.empty()) {
		delete nuevaHoja;
		return;
	}

	string claveSubir = nuevaHoja->videojuegos[0].getNombre();

	//inserto la clave en el padre
	insertarEnPadre(hoja, nuevaHoja, claveSubir, pila);

}

void ArbolBPlus::insertarEnPadre(NodoBPlus* hojaIzq, NodoBPlus* hojaDer, string claveSubir, stack<NodoBPlus*>& pila) {
	if (pila.empty()) {
		//si la pila esta vacia, significa que la hoja es la raiz
		NodoBPlus* nuevaRaiz = new NodoBPlus(false);
		nuevaRaiz->videojuegos.push_back(VideoJuego(0, claveSubir, Categoria(0,"")));
		nuevaRaiz->hijos.push_back(hojaIzq);
		nuevaRaiz->hijos.push_back(hojaDer);
		raiz = nuevaRaiz;
		return;
	}

	//agarro el padre
	NodoBPlus* padre = pila.top();
	pila.pop();

	//encuentro donde meter el padre comparando por nombre
	int posicion = 0;
	while (posicion < padre->videojuegos.size() && claveSubir > padre->videojuegos[posicion].getNombre()) {
		posicion++;
	}

	//hago un videojuego temporal para insertar en el padre
	VideoJuego temp(0, claveSubir, Categoria(0, ""));

	//inserto la clave en el padre 

	padre->videojuegos.insert(padre->videojuegos.begin() + posicion, temp);

	//Actualizo los hijos
	padre->hijos[posicion] = hojaIzq;

	padre->hijos.insert(padre->hijos.begin() + posicion + 1, hojaDer);

	//verifico si el padre necesita dividirse
	if (padre->videojuegos.size() > 4) {
		dividirNodoInterno(padre, pila);
	}
}

void ArbolBPlus::dividirNodoInterno(NodoBPlus* nodo, stack<NodoBPlus*>& pila) {
	//calculo donde divido el nodo
	int mitad = nodo->videojuegos.size() / 2;

	//la clave que sube es el nombre del videojuego que esta a la mitad
	string claveSubir = nodo->videojuegos[mitad].getNombre();

	//hago un nuevo nodo interno
	NodoBPlus* nuevoNodo = new NodoBPlus(false);

	//copio clave de la derecha despues de la mitad al nuevo nodo
	nuevoNodo->videojuegos.assign(nodo->videojuegos.begin() + mitad + 1, nodo->videojuegos.end());

	//redimensiono nodo original
	nodo->videojuegos.resize(mitad);

	//distribuyo hijos 

	nuevoNodo->hijos.assign(nodo->hijos.begin() + mitad + 1, nodo->hijos.end());

	nodo->hijos.resize(mitad + 1);

	insertarEnPadre(nodo, nuevoNodo, claveSubir, pila);

}

VideoJuego* ArbolBPlus::buscar(string nombre) {
	if (raiz->videojuegos.empty()) {
		return nullptr; //si el arbol esta vacio
	}

	NodoBPlus* nodoActual = raiz; //empiezo en la raiz

	while (!nodoActual->hoja) { //mientras no sea hoja
		int posicion = 0;
		while (posicion < nodoActual->videojuegos.size() && nombre > nodoActual->videojuegos[posicion].getNombre()) {
			posicion++;
		}
		nodoActual = nodoActual->hijos[posicion]; //bajo al hijo correspondiente
	}

	for (int i = 0; i < nodoActual->videojuegos.size(); i++) {
		if (nodoActual->videojuegos[i].getNombre() == nombre) {
			return &(nodoActual->videojuegos[i]); //si lo encuentro devuelvo el puntero al videojuego
		}
	}
	return nullptr; //si no lo encuentro devuelvo nullptr
}

void ArbolBPlus::imprimir() {
	if (raiz->videojuegos.empty()) {
		cout << "No hay datos!" << endl;
		return;
	}
	NodoBPlus* nodoActual = raiz; //empiezo en la raiz
	while (!nodoActual->hoja) { //mientras no sea hoja
		nodoActual = nodoActual->hijos[0]; //bajo al hijo izquierdo
	}
	while (nodoActual != nullptr) { //mientras haya nodos hoja
		for (int i = 0; i < nodoActual->videojuegos.size(); i++) {
			cout << "Nombre: " << nodoActual->videojuegos[i].getNombre() << ", Categoria: " << nodoActual->videojuegos[i].getCategoria().getNombre() << endl;
		}
		nodoActual = nodoActual->siguiente; //voy al siguiente nodo hoja
	}
}
