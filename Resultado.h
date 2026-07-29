#pragma once
#include <string>
#include "Juego.h"
#include "Usuario.h"

class Resultado {

private:
	int idResultado;
	int puntos;
	bool ganado;
	Juego juego;
	Usuario usuario;

public:
	Resultado() : idResultado(0), puntos(0), ganado(false) {};
	Resultado(int idResultado, int puntos, bool ganado, Juego juego, Usuario usuario) : idResultado(idResultado), puntos(puntos), ganado(ganado), juego(juego), usuario(usuario) {}

	int getIdResultado() const { return idResultado; }
	void setIdResultado(int idResultado) { this->idResultado = idResultado; }

	int getPuntos() const { return puntos; }
	void setPuntos(int puntos) { this->puntos = puntos; }

	bool isGanado() const { return ganado; }
	void setGanado(bool ganado) { this->ganado = ganado; }
	
	Juego getJuego() const { return juego; }
	void setJuego(Juego juego) { this->juego = juego; }

	Usuario getUsuario() const { return usuario; }
	void setUsuario(Usuario usuario) { this->usuario = usuario; }


};