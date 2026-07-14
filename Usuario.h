#pragma once
#pragma once

#include <string>
using namespace std;

class Usuario {
private:
	//atributos 
	int cedula;
	string nombre;
	string contrasena;
public:
	//constructores 
	Usuario() : cedula(0), nombre(""), contrasena("") {} // primero vacia
	Usuario(int cedula, const string& nombre, const string& contrasena) : cedula(cedula), nombre(nombre), contrasena(contrasena) {} // segunda con parametros

	//getters y setters
	int getCedula() const { return cedula; }
	void setCedula(int cedula) { this->cedula = cedula; }

	string getNombre() const { return nombre; }
	void setNombre(const string& nombre) { this->nombre = nombre; }

	string getContrasenna() const { return contrasena; }
	void setContrasenna(const string& contrasena) { this->contrasena = contrasena; }

};