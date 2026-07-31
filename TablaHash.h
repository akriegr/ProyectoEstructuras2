#pragma once
#include "Resultado.h"
#include <vector>

class TablaHash {

private:

	struct Nodo {
		int clave;
		Resultado valor;
		Nodo* siguiente;

		Nodo(int clave, Resultado& valor);
	};

	vector<Nodo*> tabla; //vector de punteros a listas enlazadas
	int capacidad; //capacidad de la tabla
	int tamano; // tamano actual de la tabla
	float factorCargaMaximo; // facto maximo de carga antes de que toque redimensionar

	//funcion hash para calcular el indice donde se guardan el puntero
	int funcionHash(int clave) const;

	//metodo para redimensionar la tabla cuando el factor super el maximo 
	void redimensionar();

public:
	//constructor 
	TablaHash(int capacidad = 10, float factorCargaMaximo = 0.75);
	~TablaHash();

	void insertar(const Resultado& resultado);
	Resultado* buscar(int clave);
	bool eliminar(int clave);
	void verResultados();

};
