#pragma once
#include "IResultadoDAO.h"
#include "Resultado.h"
#include <memory>

class ServicioResultado {

private: 	
	std::unique_ptr<IResultadoDAO> resultadoDAO;

public: 

	ServicioResultado(std::unique_ptr<IResultadoDAO> dao) : resultadoDAO(std::move(dao)) {}

	int insertarResultado(int puntos, bool ganado, int idJuego, int idJugador) {
		bool resultado = resultadoDAO->insertar(puntos, ganado, idJuego, idJugador);
		return resultado;
	}

	std::vector <Resultado> obtenerResultados() {
		return resultadoDAO->obtenerResultados();
	}

	bool actualizarResultado(int idResultado, int puntajeNuevo) {
		return resultadoDAO->actualizar(idResultado, puntajeNuevo);
	}

	bool eliminarResultado(int idResultado) {
		return resultadoDAO->eliminar(idResultado);
	}
};
