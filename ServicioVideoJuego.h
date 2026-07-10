#pragma once
#include "IVideoJuegoDAO.h"
#include "VideoJuego.h"
#include <memory>

class ServicioVideoJuego {

private:
	std::unique_ptr<IVideoJuegoDAO> videojuegoDAO;

public:
	ServicioVideoJuego(std::unique_ptr<IVideoJuegoDAO> dao) : videojuegoDAO(std::move(dao)) {}

	void insertarVideoJuego(string nombre, int idCategoria) {
		int resultado =  videojuegoDAO->insertar(nombre,idCategoria);
		if (resultado == 1) {
			cout << "VideoJuego insertado exitosamente" << endl;
		}else if(resultado == 2){
			cout << "Error al insertar el videojuego" << endl;
		}
		else if (resultado == 3) {
			cout << "Error en la base de datos!" << endl;
		}
	}

	//metodos para interactuar con la bd
	/*

	std::optional<VideoJuego> obtenerVideoJuegoPorId(int id) {
		return videojuegoDAO->obtenerPorId(id);
	}
	bool actualizarVideoJuego(const VideoJuego& videojuego) {
		return videojuegoDAO->actualizar(videojuego);
	}
	*/
	std::vector<VideoJuego> obtenerTodosVideoJuegos() {
		return videojuegoDAO->ObtenerVideoJuegos();
	}
};