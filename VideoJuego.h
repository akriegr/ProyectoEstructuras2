#pragma once
#include <string>
#include "Categoria.h"

class VideoJuego{
private:
	int id;
	string nombre;
	Categoria categoria;

public:
	VideoJuego() :id(0), nombre("") {}
	VideoJuego(int id, const string& nombre, Categoria categoria) :id(id), nombre(nombre), categoria(categoria) {}

	//gettes y setters
	int getId()const { return id; }
	void setId(int id) { this->id = id; }
	
	string getNombre() const { return nombre; }
	void setNombre(const string& nombre) { this->nombre = nombre; }

	Categoria getCategoria()const { return categoria; }
	void setCategoria(Categoria categoria) { this->categoria = categoria; }

};