#include "ArbolRN.h"
#include <iostream>
#include <algorithm>
using namespace std;

NodoRN::NodoRN(const Usuario& usuario) : usuario(usuario), izquierda(nullptr), derecha(nullptr), padre(nullptr), esRojo(true) {}

//constructor y destructor del arbol
ArbolRN::ArbolRN() { //inicio el arbol con un nodo centinela (nullptr)
	nil = new NodoRN(Usuario()); // nodo centinela
	nil->esRojo = false; 
	nil->izquierda = nullptr;
	nil->derecha = nullptr;
	nil->padre = nullptr;
	raiz = nil;
}

ArbolRN::~ArbolRN() {
	destruirArbol(raiz);
	delete nil;
}

void ArbolRN::destruirArbol(NodoRN* nodo) {
	if (nodo != nil) {
		destruirArbol(nodo->izquierda);
		destruirArbol(nodo->derecha);
		delete nodo;
	}
}

//rotaciones 

void ArbolRN::rotarIzquierda(NodoRN* x) {
	NodoRN* y = x->derecha; //el nodo y es el hijo derecho de x 

	x->derecha = y->izquierda; //el hijo derecho de x se convierte en el hijo izquierdo de y

	if (y->izquierda != nil) { // si el hijo izquierdo y es diferente de nil, entonces el padre del hijo izquierdo de y es x
		y->izquierda->padre = x;
	}

	y->padre = x->padre; // el padre de y se convierte en el padre de x

	if (x->padre == nil) { // si x es la raiz, entonces la raiz se convierte en y
		raiz = y;
	}
	else if (x == x->padre->izquierda) { //si x es el hijo izquierdo de su padre, entonces el hijo izquierdo del padre de x es y
		x->padre->izquierda = y;
	}
	else {//si x es el hijo derecho de su padre, entonces el hijo derecho del padre de x es y
		x->padre->derecha = y;
	}
	y->izquierda = x; //el hijo izquierdo de y se convierte en x
	x->padre = y; //el padre de x se convierte en y
}

void ArbolRN::rotarDerecha(NodoRN* x) {
	NodoRN* y = x->izquierda; //el nodo y es el hijo izquierdo de x
	x->izquierda = y->derecha; //el hijo izquierdo de x se convierte en el hijo derecho de y
	
	if (y->derecha != nil) { // si el hijo derecho y es diferente de nil, entonces el padre del hijo derecho de y es x
		y->derecha->padre = x;
	}
	
	y->padre = x->padre; // el padre de y se convierte en el padre de x
	
	if (x->padre == nil) { // si x es la raiz, entonces la raiz se convierte en y
		raiz = y;
	}
	else if (x == x->padre->derecha) { //si x es el hijo derecho de su padre, entonces el hijo derecho del padre de x es y
		x->padre->derecha = y;
	}
	else {//si x es el hijo izquierdo de su padre, entonces el hijo izquierdo del padre de x es y
		x->padre->izquierda = y;
	}
	
	y->derecha = x; //el hijo derecho de y se convierte en x
	
	x->padre = y; //el padre de x se convierte en y
}

//Balance de insercio

void ArbolRN::balancearInsercion(NodoRN* z) {
	while (z->padre->esRojo) {
		if (z->padre == z->padre->padre->izquierda) {
			NodoRN* tio = z->padre->padre->derecha;

			if (tio->esRojo) {
				// Caso 1: El tío es rojo
				z->padre->esRojo = false;
				tio->esRojo = false;
				z->padre->padre->esRojo = true;
				z = z->padre->padre;
			}
			else {
				// Caso 2: El tío es negro
				if (z == z->padre->derecha) {
					z = z->padre;
					rotarIzquierda(z);
				}
				// Caso 3
				z->padre->esRojo = false;
				z->padre->padre->esRojo = true;
				rotarDerecha(z->padre->padre);
			}
		}
		else {
			// Simétrico
			NodoRN* tio = z->padre->padre->izquierda;

			if (tio->esRojo) {
				z->padre->esRojo = false;
				tio->esRojo = false;
				z->padre->padre->esRojo = true;
				z = z->padre->padre;
			}
			else {
				if (z == z->padre->izquierda) {
					z = z->padre;
					rotarDerecha(z);
				}
				z->padre->esRojo = false;
				z->padre->padre->esRojo = true;
				rotarIzquierda(z->padre->padre);
			}
		}
	}
	raiz->esRojo = false;
}


void ArbolRN::balancearEliminacion(NodoRN* x) {
	while (x != raiz && !x->esRojo) {
		if (x == x->padre->izquierda) {
			NodoRN* w = x->padre->derecha;

			if (w->esRojo) {
				w->esRojo = false;
				x->padre->esRojo = true;
				rotarIzquierda(x->padre);
				w = x->padre->derecha;
			}

			if (!w->izquierda->esRojo && !w->derecha->esRojo) {
				w->esRojo = true;
				x = x->padre;
			}
			else {
				if (!w->derecha->esRojo) {
					w->izquierda->esRojo = false;
					w->esRojo = true;
					rotarDerecha(w);
					w = x->padre->derecha;
				}
				w->esRojo = x->padre->esRojo;
				x->padre->esRojo = false;
				w->derecha->esRojo = false;
				rotarIzquierda(x->padre);
				x = raiz;
			}
		}
		else {
			NodoRN* w = x->padre->izquierda;

			if (w->esRojo) {
				w->esRojo = false;
				x->padre->esRojo = true;
				rotarDerecha(x->padre);
				w = x->padre->izquierda;
			}

			if (!w->derecha->esRojo && !w->izquierda->esRojo) {
				w->esRojo = true;
				x = x->padre;
			}
			else {
				if (!w->izquierda->esRojo) {
					w->derecha->esRojo = false;
					w->esRojo = true;
					rotarIzquierda(w);
					w = x->padre->izquierda;
				}
				w->esRojo = x->padre->esRojo;
				x->padre->esRojo = false;
				w->izquierda->esRojo = false;
				rotarDerecha(x->padre);
				x = raiz;
			}
		}
	}
	x->esRojo = false;
}

void ArbolRN :: transplantar(NodoRN* u, NodoRN* v){
	if (u->padre == nil) {
		raiz = v;
	}
	else if (u == u->padre->izquierda) {
		u->padre->izquierda = v;
	}
	else {
		u->padre->derecha = v;
	}
	v->padre = u->padre;
}

NodoRN* ArbolRN::minimo(NodoRN* nodo) const {
	while (nodo->izquierda != nil) {
		nodo = nodo->izquierda;
	}
	return nodo;
}

void ArbolRN::eliminarNodo(NodoRN* z) {
	if (z == nil) return;

	NodoRN* y = z;
	NodoRN* x;
	bool yColorOriginal = y->esRojo;

	if (z->izquierda == nil) {
		x = z->derecha;
		transplantar(z, z->derecha);
	}
	else if (z->derecha == nil) {
		x = z->izquierda;
		transplantar(z, z->izquierda);
	}
	else {
		y = minimo(z->derecha);
		yColorOriginal = y->esRojo;
		x = y->derecha;

		if (y->padre == z) {
			x->padre = y;
		}
		else {
			transplantar(y, y->derecha);
			y->derecha = z->derecha;
			y->derecha->padre = y;
		}

		transplantar(z, y);
		y->izquierda = z->izquierda;
		y->izquierda->padre = y;
		y->esRojo = z->esRojo;
	}

	if (!yColorOriginal) {
		balancearEliminacion(x);
	}

	delete z;
}

NodoRN* ArbolRN::buscarPorNombre(NodoRN* nodo, const string& nombre) const {
	if (nodo == nil) {
		return nullptr;
	}

	if (nombre == nodo->usuario.getNombre()) {
		return nodo;
	}
	else if (nombre < nodo->usuario.getNombre()) {
		return buscarPorNombre(nodo->izquierda, nombre);
	}
	else {
		return buscarPorNombre(nodo->derecha, nombre);
	}
}

void ArbolRN::imprimirEnOrden(NodoRN* nodo) const {
	if (nodo != nil) {
		imprimirEnOrden(nodo->izquierda);
		cout << "Nombre: " << nodo->usuario.getNombre()
			<< " (Cedula: " << nodo->usuario.getCedula() << ")"
			/* << " Color: " << (nodo->esRojo ? "ROJO" : "NEGRO")*/ << endl;
		imprimirEnOrden(nodo->derecha);
	}
}

void ArbolRN::insertar(const Usuario& usuario) {
	NodoRN* z = new NodoRN(usuario);
	NodoRN* y = nil;
	NodoRN* x = raiz;

	// Buscar posición de inserción (ordenado por nombre)
	while (x != nil) {
		y = x;
		if (z->usuario.getNombre() < x->usuario.getNombre()) {
			x = x->izquierda;
		}
		else {
			x = x->derecha;
		}
	}

	z->padre = y;

	if (y == nil) {
		raiz = z;
	}
	else if (z->usuario.getNombre() < y->usuario.getNombre()) {
		y->izquierda = z;
	}
	else {
		y->derecha = z;
	}

	z->izquierda = nil;
	z->derecha = nil;
	z->esRojo = true;

	balancearInsercion(z);
}

bool ArbolRN::eliminar(const string& nombre) {
	NodoRN* nodo = buscarPorNombre(raiz, nombre);
	if (nodo == nullptr) {
		return false;
	}
	eliminarNodo(nodo);
	return true;
}

Usuario* ArbolRN::buscar(const string& nombre) const {
	NodoRN* nodo = buscarPorNombre(raiz, nombre);
	if (nodo != nullptr) {
		return &(nodo->usuario);
	}
	return nullptr;
}

void ArbolRN::imprimir() const {
	if (raiz == nil) {
		cout << "El árbol está vacío" << endl;
		return;
	}
	cout << "\n*****Lista Usuarios*****" << endl;
	imprimirEnOrden(raiz);
	cout << "**********************************" << endl;
}

