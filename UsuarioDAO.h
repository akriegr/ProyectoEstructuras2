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
	bool insertarUsuario(int cedula, string nombre, string contrasena) override;
	virtual vector <Usuario>ObtenerUsuarios() override;
	virtual bool eliminarUsuario(int id) override;
	virtual bool actualizarUsuario(int idUsuario, string nombreNuevo) override;
};