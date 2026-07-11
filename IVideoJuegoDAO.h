#pragma once
#include "VideoJuego.h"
#include <vector>
#include <optional>
#include "DBManager.h"

class IVideoJuegoDAO {
	//interfaz de categoriaDAO, defino cuales operaciones se pueden hacer 
public:
	virtual ~IVideoJuegoDAO() = default;

	//Crud basico
	virtual int insertar(string nombre, int idCategoria) = 0;
	//virtual optional<VideoJuego> obtenerPorId(int id) = 0;
	virtual vector <VideoJuego>ObtenerVideoJuegos() = 0;
	virtual bool actualizar(int idVideoJuego, string nombreNuevo) = 0;
	//virtual bool eliminar(int id) = 0;	

	//Consultas adicionales

};
