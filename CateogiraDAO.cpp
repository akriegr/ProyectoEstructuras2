#include "CategoriaDAO.h"
#include <iostream>
#include <sstream>

CategoriaDAO::CategoriaDAO(DBManager& manager) : dbManager(manager) {
	if (!dbManager.isConnected()) {
		dbManager.connect();
	}
}

//metodo para mapear result ser a categoria
Categoria CategoriaDAO::mapResultSet(sql::ResultSet* rs) {
	int id = rs->getInt("id_categoria");
	std::string nombre = rs->getString("nombre").c_str();
	return Categoria(id, nombre);
}

//CRUD 

//READ 
std::vector<Categoria> CategoriaDAO::ObtenerCategorias() {
	std::vector<Categoria> categorias;
	try {
		std::string query = "SELECT * FROM categoria";

		// Obtener Statement y ResultSet juntos
		auto [stmt, rs] = dbManager.executeQueryWithStatement(query);

		while (rs->next()) {
			Categoria cat = mapResultSet(rs.get());
			categorias.push_back(cat);
		}
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Error fetching categories: " << e.what() << std::endl;
	}
	return categorias;
}