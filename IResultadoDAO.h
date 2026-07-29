#pragma once
#include <vector>
#include <optional>
#include "Resultado.h"
#include "DBManager.h"


class IResultadoDAO {
public: 
	virtual ~IResultadoDAO() = default;
	//Crud basico
	virtual bool insertar(int puntos,bool ganado, int idJuego, int idJugador) = 0;
	//virtual optional<Juego> obtenerPorId(int id) = 0;
	virtual std::vector <Resultado>obtenerResultados() = 0;
	virtual bool actualizar(int idResultado, int puntajeNuevo) = 0;
	virtual bool eliminar(int idResultado) = 0;

};
