#pragma once
#include "IUsuarioDAO.h"
#include <mariadb/conncpp.hpp>
#include <memory>

class UsuarioDAO : public IUsuarioDAO {
private: 
	DBManager& dbManager;
	Usuario mapResultSet(sql::ResultSet* rs);
public:
	UsuarioDAO(DBManager& manager);
	virtual vector <Usuario>ObtenerUsuarios() override;
};