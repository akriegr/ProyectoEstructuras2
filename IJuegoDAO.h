#pragma once
#include "Juego.h"
#include <vector>
#include <optional>
#include "DBManager.h"

class IJuegoDAO {
	//interfaz de categoriaDAO, defino cuales operaciones se pueden hacer 
public:
	virtual ~IJuegoDAO() = default;

	//Crud basico
	virtual bool insertar(string fecha, int idVideoJuego) = 0;
	//virtual optional<Juego> obtenerPorId(int id) = 0;
	virtual vector <Juego>obtenerJuegos() = 0;
	virtual bool actualizar(int idJuego, string fecha) = 0;
	virtual bool eliminar(int idJuego) = 0;

};