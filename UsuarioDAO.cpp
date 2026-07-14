#include"UsuarioDAO.h"
#include <iostream>
#include <sstream>

UsuarioDAO::UsuarioDAO(DBManager& manager) : dbManager(manager) {
	if (!dbManager.isConnected()) {
		dbManager.connect();
	}
}

//metodo para mapear result set a usuario
Usuario UsuarioDAO::mapResultSet(sql::ResultSet* rs) {
	int id = rs->getInt("cedula");
	std::string nombre = rs->getString("nombre").c_str();
	std::string contrasena= rs->getString("contrasena").c_str();

	return Usuario(id, nombre, contrasena);
}

//CRUD 

//READ
vector<Usuario> UsuarioDAO::ObtenerUsuarios() {
	std::vector<Usuario> usuarios;
	try {
		std::string query = "SELECT * FROM usuario";
		// Obtener Statement y ResultSet juntos
		auto [stmt, rs] = dbManager.executeQueryWithStatement(query);
		while (rs->next()) {
			Usuario user = mapResultSet(rs.get());
			usuarios.push_back(user);
		}
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Error fetching users: " << e.what() << std::endl;
	}
	return usuarios;
}