#pragma once

#include <string>
using namespace std;

class Categoria {
private: 
	//atributos 
	int id;
	string nombre;
public:
	//constructores 
	Categoria() : id(0), nombre("") {} // primero vacia
	Categoria(int id, const string& nombre) : id(id), nombre(nombre) {} // segunda con parametros
	
	//getters y setters
	int getId() const { return id; }
	void setId(int id) { this->id = id; }

	string getNombre() const { return nombre; }
	void setNombre(const string& nombre) { this->nombre = nombre; }

};
