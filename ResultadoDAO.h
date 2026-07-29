#pragma once
#include "IResultadoDAO.h"
#include <mariadb/conncpp.hpp>
#include <memory>

class ResultadoDAO : public IResultadoDAO {

private:
	DBManager& dbManager;
	Resultado mapResultSet(sql::ResultSet* rs);

public:
	ResultadoDAO(DBManager& manager);
	virtual bool insertar(int puntos, bool ganado, int idJuego, int idJugador) override;
	virtual vector <Resultado>obtenerResultados() override;
	virtual bool actualizar(int idResultado, int puntajeNuevo) override;
	virtual bool eliminar(int idResultado)override;

};