#pragma once
#include "ICategoriaDAO.h"
#include <mariadb/conncpp.hpp>
#include <memory>

class CategoriaDAO : public ICategoriaDAO {

private:
	DBManager& dbManager;
	Categoria mapResultSet(sql::ResultSet* rs);

public:
	CategoriaDAO(DBManager& manager);
	//bool insertar(const Categoria& categoria) override;
	virtual optional<Categoria> obtenerPorId(int id) override;
	virtual vector <Categoria>ObtenerCategorias() override;
	//virtual bool actualizar(const Categoria& categoria) override;
	//virtual bool eliminar(int id) override;

};