#include "TablaHash.h"
#include <iostream>
using namespace std;

TablaHash::Nodo::Nodo(int clave, Resultado& valor) : clave(clave), valor(valor), siguiente(nullptr) {}

int TablaHash::funcionHash(int clave) const {
	return clave % capacidad;
}

void TablaHash::redimensionar() {
	int nuevaCapacidad = capacidad * 2; // duplico capacidad
	vector<Nodo*> nuevaTabla(nuevaCapacidad, nullptr); // inicializo una nueva tabla con la capacidad duplicada
	for (int i = 0; i < capacidad; ++i) {
		Nodo* actual = tabla[i];
		while (actual != nullptr) {//mientras que el nodo en el que estoy no sea null
			Nodo* siguiente = actual->siguiente;
			int nuevoIndice = funcionHash(actual->clave); //calculo el nuevo indice para el nodo actual
			actual->siguiente = nuevaTabla[nuevoIndice]; //apunto el siguiente del nodo actual al nodo que esta en el nuevo indice
			nuevaTabla[nuevoIndice] = actual; //inserto el nodo actual en la nueva tabla
			actual = siguiente; //muevo al siguiente nodo
		}
	}
	tabla = move(nuevaTabla);
	capacidad = nuevaCapacidad;
}

TablaHash::TablaHash(int capacidad, float factorCargaMaximo) : capacidad(capacidad), tamano(0), factorCargaMaximo(factorCargaMaximo) {
	if (capacidad < 1) {
		capacidad = 10; // valor por defecto si la capacidad es menor a 1
	}
	if (factorCargaMaximo <= 0 || factorCargaMaximo >= 1) {
		factorCargaMaximo = 0.75; // valor por defecto si el factor de carga es menor o igual a 0 o mayor a 1
	}
	tabla.resize(capacidad, nullptr); // inicializo la tabla con la capacidad especificada
}

TablaHash :: ~TablaHash() {
	for (int i = 0; i < capacidad; ++i) {
		Nodo* actual = tabla[i];
		while (actual != nullptr) {
			Nodo* siguiente = actual->siguiente;
			delete actual; //libero memoria del nodo actual
			actual = siguiente; //muevo al siguiente nodo
		}
	}
}

void TablaHash::insertar(const Resultado& resultado) {
	int clave = resultado.getIdResultado(); // obtengo la clave de la cuenta
	int indice = funcionHash(clave); // calculo el indice donde se guardara la cuenta

	//buscar si ya exista la cuenta
	Nodo* actual = tabla[indice];
	while (actual != nullptr) {
		if (actual->clave == clave) {
			actual->valor = resultado; // si la cuenta ya existe, actualizo su valor
			return;
		}
		actual = actual->siguiente; //muevo al siguiente nodo
	}

	//meter un nuevo nodo 
	Nodo* nuevoNodo = new Nodo(clave, const_cast<Resultado&>(resultado)); // creo un nuevo nodo con la cuenta
	nuevoNodo->siguiente = tabla[indice]; // apunto el siguiente del nuevo nodo al nodo que esta en el indice
	tabla[indice] = nuevoNodo; // inserto el nuevo nodo en la tabla
	tamano++; // incremento el tamaño de la tabla

	//reviso factor de carga
	float factorCarga = static_cast<float>(tamano) / capacidad; // calculo el factor de carga
	if (factorCarga > factorCargaMaximo) {
		redimensionar(); // si el factor de carga es mayor al maximo, redimensiono la tabla
	}
}

Resultado* TablaHash::buscar(int idResultado) {//cuando busco devuelvo un puntero a una cuenta
	int indice = funcionHash(idResultado); // calculo el indice donde se encuentra la cuenta
	Nodo* actual = tabla[indice]; // obtengo el nodo que esta en el indice
	while (actual != nullptr) {
		if (actual->clave == idResultado) {
			return &(actual->valor); // si encuentro la cuenta, devuelvo un puntero a la cuenta
		}
		actual = actual->siguiente; //paso al siguiente
	}
	return nullptr; // si no encuentro la cuenta, devuelvo nullptr

};

bool TablaHash::eliminar(int idResultado) {
	int indice = funcionHash(idResultado); // calculo el indice donde se encuentra la cuenta
	Nodo* actual = tabla[indice]; // obtengo el nodo que esta en el indice
	Nodo* anterior = nullptr; // puntero al nodo anterior lo empiezo como null 

	while (actual != nullptr) {
		if (actual->clave == idResultado) {
			if (anterior == nullptr) {
				tabla[indice] = actual->siguiente;
			}
			else {
				anterior->siguiente = actual->siguiente; // si encuentro la cuenta, apunto el siguiente del nodo anterior al siguiente del nodo actual
			}
			delete actual;
			tamano--; // decremento el tamaño de la tabla
			return true;
		}
		anterior = actual;
		actual = actual->siguiente;
	}
	return false;
}

void TablaHash::verResultados() {
	bool hayResultados = false;

	for (int i = 0; i < capacidad;i++) {
		Nodo* actual = tabla[i];
		while (actual != nullptr) {
			string ganado = "";
            if (actual->valor.isGanado()==true) {
                ganado = "Si";
            }
            else {
				ganado = "No";
            }
            cout << "ID: " << actual->valor.getIdResultado() << ", VideoJuego: " << actual->valor.getJuego().getVideoJuego().getNombre() << " Ganado: " << ganado << " Puntos: " << actual->valor.getPuntos() << " Usuario: " << actual->valor.getUsuario().getNombre() << endl;
			actual = actual->siguiente;
			hayResultados = true;
		}
	}

	if (!hayResultados) {
		cout << "No hay resultados." << endl;
		return;
	}

}