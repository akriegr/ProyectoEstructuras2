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
	std::string correo = rs->getString("correo").c_str();

	return Usuario(id, nombre, contrasena, correo);
}

//CRUD 

//CREATE

bool UsuarioDAO::insertarUsuario(int cedula, string nombre, string contrasena,string correo) {
	try {
		string query = "INSERT INTO usuario(cedula, nombre, contrasena, correo) VALUES (" + std::to_string(cedula) + ",'" + nombre + "','" + contrasena + "','" + correo + "')";

		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);

		if (filasAfectadas > 0) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (const sql::SQLException& e) {
		cerr << "Error inserting usuario: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}

//READ
vector<Usuario> UsuarioDAO::ObtenerUsuarios() {
	std::vector<Usuario> usuarios;
	try {
		std::string query = "SELECT * FROM usuario";
		// Obtener Statement y ResultSet juntos
		auto [stmt, rs] = dbManager.executeQueryWithStatement(query);
		while (rs->next()) {
			Usuario usuario = mapResultSet(rs.get());
			usuarios.push_back(usuario);
		}
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Error fetching usuario: " << e.what() << std::endl;
	}
	return usuarios;
}

//update 

bool UsuarioDAO::actualizarUsuario(int idUsuario, std::string nombreNuevo) {
	try {
		std::string query = "UPDATE usuario SET nombre = '" + nombreNuevo + "' WHERE cedula = " + std::to_string(idUsuario);
		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);
		delete stmt;
		return filasAfectadas > 0; // Retorna true si se actualizó al menos una fila
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Error updating user: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}

// delete
bool UsuarioDAO::eliminarUsuario(int id) {
	try {
		std::string query = "DELETE FROM usuario WHERE cedula = " + std::to_string(id);
		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);
		delete stmt;
		return filasAfectadas > 0; // Retorna true si se eliminó al menos una fila
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Error deleting usuario: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}