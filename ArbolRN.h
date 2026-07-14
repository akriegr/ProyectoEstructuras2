#pragma once
#include <string>
#include "Usuario.h"
using namespace std;

struct NodoRN {
	Usuario usuario; // objeto Usuario
	NodoRN* izquierda; // puntero al hijo izquierdo
	NodoRN* derecha; // puntero al hijo derecho
	NodoRN* padre; // puntero al padre
	bool esRojo; // true = rojo

	NodoRN(const Usuario& usuario); // constructor
};

class ArbolRN {

private:
	NodoRN* raiz; // puntero a la raiz del arbol
	NodoRN* nil; // nodo centinela, reemplaza el nodo nullptr
	void rotarIzquierda(NodoRN* x); //metodo para rotar a la izquierda
	void rotarDerecha(NodoRN* x); //metodo para rotar a la derecha
	void balancearInsercion(NodoRN* z); //metodo para balancear el arbol despues de insertar
	void balancearEliminacion(NodoRN* x); //metodo para balancear el arbol despues de eliminar
	void transplantar(NodoRN* u, NodoRN* v);//metodo para reemplazar un nodo por otro
	NodoRN* minimo(NodoRN* nodo) const; //metodo para encontrar el nodo minimo
	void eliminarNodo(NodoRN* z); //metodo para eliminar un nodo)
	NodoRN* buscarPorNombre(NodoRN* nodo, const string& nombre) const; //metodo para buscar un nodo por nombre
	void imprimirEnOrden(NodoRN* nodo) const; //metodo para imprimir el arbol en orden
	void destruirArbol(NodoRN* nodo);

public:
	ArbolRN(); //constructor
	~ArbolRN(); // destructor

	void insertar(const Usuario& usuario); //metodo para insertar un nuevo usuario
	bool eliminar(const string& nombre); //metodo para eliminar un usuario por nombre
	Usuario* buscar(const string& nombre) const; //metodo para buscar un usuario por nombre
	bool existe(const string& nombre) const; //metodo para verificar si un usuario existe por nombre
	void imprimir() const; //metodo para imprimir el arbol en orden

};