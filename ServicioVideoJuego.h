#pragma once
#include "IVideoJuegoDAO.h"
#include "VideoJuego.h"
#include <memory>

class ServicioVideoJuego {

private:
	std::unique_ptr<IVideoJuegoDAO> videojuegoDAO;

public:
	ServicioVideoJuego(std::unique_ptr<IVideoJuegoDAO> dao) : videojuegoDAO(std::move(dao)) {}

	int insertarVideoJuego(string nombre, int idCategoria) {
		int resultado =  videojuegoDAO->insertar(nombre,idCategoria);
		return resultado;
	}

	std::vector<VideoJuego> obtenerTodosVideoJuegos() {
		return videojuegoDAO->ObtenerVideoJuegos();
	}

	bool actualizarVideoJuego(int idVideoJuego, string nombre) {
		return videojuegoDAO->actualizar(idVideoJuego,nombre);
	}

	bool eliminarVideoJuego(int id) {
		return videojuegoDAO->eliminar(id);
	}

	//metodos para interactuar con la bd
	/*

	std::optional<VideoJuego> obtenerVideoJuegoPorId(int id) {
		return videojuegoDAO->obtenerPorId(id);
	}

	*/

};