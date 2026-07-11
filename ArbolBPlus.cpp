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

ArbolBPlus :: ~ArbolBPlus() {
	destruirArbol(); //llamo al metodo para destruir el arbol
}

void ArbolBPlus::destruirArbol() {
	if (raiz != nullptr) {
		destruirNodo(raiz); //llamo al metodo recursivo para destruir el nodo
		raiz = nullptr; //pongo la raiz en null
	}
}

void ArbolBPlus::destruirNodo(NodoBPlus* nodo) {

	if (nodo == nullptr) {//si el nodo es null me devuelvo
		return;
	} 

	//si no es hoja, destruyo todos los hijos de forma recursiva
	if (!nodo->hoja) {
		for (NodoBPlus* hijo : nodo->hijos) {
			destruirNodo(hijo);
		}
	}

	//limpio vectores
	nodo->videojuegos.clear();
	nodo->hijos.clear();

	delete nodo; //libero memoria del nodo
}

void ArbolBPlus::vaciarArbol() {
	if (raiz != nullptr) {
		//mantengo solo los hijos de la raiz 
		if (!raiz->hoja) {//si no es hoja
			for (NodoBPlus* hijo : raiz->hijos) {
				destruirNodo(hijo); //destruyo los hijos de la raiz
			}
			raiz->hijos.clear();//limpio el vector de hijos de la raiz
		}
		raiz->videojuegos.clear(); //limpio el vector de videojuegos de la raiz
	}
}

bool ArbolBPlus::eliminarVideoJuego(string nombre) {
	if (raiz->videojuegos.empty()) {
		return false; // me devuelvo porque el arbol esta vacio
	}

	//Busco la hoja que contiene el videojuego a eliminar
	NodoBPlus* nodoActual = raiz;
	stack<NodoBPlus*> pila; //pila para almacenar los nodos visitados	

	while (!nodoActual->hoja) {
		pila.push(nodoActual); //guardo el nodo actual en la pila
		int posicion = 0;
		while (posicion < nodoActual->videojuegos.size() && nombre > nodoActual->videojuegos[posicion].getNombre()) {
			posicion++;
		}
		nodoActual = nodoActual->hijos[posicion]; //me muevo al hijo correspondiente
	}
	NodoBPlus* hoja = nodoActual; //la hoja donde se encuentra el videojuego a eliminar

	//reviso si existe el videojuego en la hoja
	bool encontrado = false;
	for (int i = 0; i < hoja->videojuegos.size(); i++) {
		if (hoja->videojuegos[i].getNombre() == nombre) {
			hoja->videojuegos.erase(hoja->videojuegos.begin() + i);
			encontrado = true;
			break;
		}
	}

	if (!encontrado) {
		return false;
	}

	//si la hoja queda vacia o tiene pocos elementos rebalancear

	if (hoja->videojuegos.empty() && raiz != hoja) {
		
		//la hoja esta vacia rebalanceo, elimino la hoja y fusiono con el nodo hermano
		NodoBPlus* padre = pila.empty() ? nullptr : pila.top();

		if (padre != nullptr) {
			int posicion = 0;
			while (posicion < padre->hijos.size() && padre->hijos[posicion] != hoja) {
				posicion++;
			}
			if (posicion < padre->hijos.size()) {
				//intento prestar de algun hermano
				if (posicion > 0 && padre->hijos[posicion - 1]->videojuegos.size() > 2) {
					prestarIzquierda(padre, posicion);
				}
				else if (posicion < padre->hijos.size() - 1 && padre->hijos[posicion + 1]->videojuegos.size() > 2) {
					prestarDerecha(padre, posicion);
				}
				else {
					if (posicion > 0) {
						fusionar(padre, posicion - 1);
					}
					else {
						fusionar(padre, posicion);
					}
				}
			}
		
		}

	}
	return true;
}

bool ArbolBPlus::actualizarVideoJuego(string nombre, string nuevoNombre) {
	//busco el videojuego en el arbol
	VideoJuego* videojuegoExistente = buscar(nombre);
	if (videojuegoExistente == nullptr) {
		return false; //no existe el videojuego
	}
	VideoJuego* videoJuegoActualizado = new VideoJuego(videojuegoExistente->getId(),nuevoNombre,videojuegoExistente->getCategoria());

	//actualizo el videojuego (solo cambio el nombre)
	eliminarVideoJuego(videojuegoExistente->getNombre()); //lo elimino del arbol
	insertarVideoJuego(*videoJuegoActualizado); //lo inserto con el nuevo nombre)
	return true;
}

void ArbolBPlus::prestarIzquierda(NodoBPlus* padre, int posicion) {
	NodoBPlus* izquierdo = padre->hijos[posicion-1];
	NodoBPlus* derecho = padre->hijos[posicion];

	//mover el primer videojuego del hijo derecho al izquierdo
	VideoJuego temp = izquierdo->videojuegos.back();
	izquierdo->videojuegos.pop_back();
	derecho->videojuegos.insert(derecho->videojuegos.begin(), temp);

	padre->videojuegos[posicion - 1] = derecho->videojuegos[0]; //actualizo la clave en el padre
}

void ArbolBPlus::prestarDerecha(NodoBPlus* padre, int posicion){
	NodoBPlus* izquierdo = padre->hijos[posicion];
	NodoBPlus* derecho = padre->hijos[posicion + 1];

	//mover el primer videojuego del hijo derecho al izquierdo
	VideoJuego temp = derecho->videojuegos[0];
	derecho->videojuegos.erase(derecho->videojuegos.begin());
	izquierdo->videojuegos.push_back(temp);

	padre->videojuegos[posicion] = derecho->videojuegos[0]; //actualizo la clave en el padre
}

void ArbolBPlus::fusionar(NodoBPlus* padre, int posicion) {
	NodoBPlus* izquierdo = padre->hijos[posicion];
	NodoBPlus* derecho = padre->hijos[posicion + 1];

	//muevo todos los videojuegos del hijo derecho al izquierdo
	izquierdo->videojuegos.insert(izquierdo->videojuegos.end(), derecho->videojuegos.begin(), derecho->videojuegos.end());
	
	//actualizo el enlace siguiente
	izquierdo->siguiente = derecho->siguiente;

	//Eliminar nodo derecho y clave de padre
	padre->hijos.erase(padre->hijos.begin() + posicion + 1);
	padre->videojuegos.erase(padre->videojuegos.begin() + posicion);

	//si el padre queda vacio se vuelve raiz 

	if (padre->videojuegos.empty() && padre == raiz) {
		NodoBPlus* nuevaRaiz = padre->hijos[0];
		padre->hijos.clear();
		delete padre;
		raiz = nuevaRaiz;
	}
	delete derecho;
}

void ArbolBPlus::insertarVideoJuego(VideoJuego videojuego) {
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
			cout <<" Nombre: " << nodoActual->videojuegos[i].getNombre() << " Categoria: " << nodoActual->videojuegos[i].getCategoria().getNombre() << endl;
		}
		nodoActual = nodoActual->siguiente; //voy al siguiente nodo hoja
	}
}
