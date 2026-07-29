#pragma once
#include "IJuegoDAO.h"
#include "Juego.h"
#include <memory>

class ServicioJuego {

private:
	std::unique_ptr<IJuegoDAO> juegoDAO;

public:
	ServicioJuego(std::unique_ptr<IJuegoDAO> dao) : juegoDAO(std::move(dao)) {}

	int insertarJuego(string fecha, int idVideojuego) {
		int resultado = juegoDAO->insertar(fecha, idVideojuego);
		return resultado;
	}

	std::vector<Juego> obtenerJuegos() {
		return juegoDAO->obtenerJuegos();
	}

	bool actualizarJuego(int idJuego, string fechaNueva) {
		return juegoDAO->actualizar(idJuego, fechaNueva);
	}

	bool eliminarJuego(int idJuego) {
		return juegoDAO->eliminar(idJuego);
	}


};