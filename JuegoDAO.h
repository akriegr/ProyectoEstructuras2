#pragma once
#include "IJuegoDAO.h"
#include <mariadb/conncpp.hpp>
#include <memory>

class JuegoDAO :public IJuegoDAO {

private:
	DBManager& dbManager;
	Juego mapResultSet(sql::ResultSet* rs);

public: 

	JuegoDAO(DBManager& manager);
	virtual bool insertar(string fecha, int id_videojuego) override;
	virtual vector<Juego>obtenerJuegos() override;
	virtual bool actualizar(int idJuego, string fechaNueva) override;
	virtual bool eliminar(int idJuego)override;

};