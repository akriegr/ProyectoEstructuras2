#include "VideoJuegoDAO.h"
#include "CategoriaDAO.h"
#include <iostream>
#include <sstream>

VideoJuegoDAO::VideoJuegoDAO(DBManager& manager) : dbManager(manager) {
	if (!dbManager.isConnected()) {
		dbManager.connect();
	}
}

//metodo para mapear result a videojuego
VideoJuego VideoJuegoDAO::mapResultSet(sql::ResultSet* rs) {
	int id = rs->getInt("id_videojuego");
	std::string nombre = rs->getString("nombre").c_str();
	int id_categoria = rs->getInt("id_categoria");
	std::string nombre_categoria = rs->getString("nombre_categoria").c_str();
	Categoria categoria(id_categoria, nombre_categoria);
	return VideoJuego(id, nombre, categoria);
}

//CRUD

//READ

std::vector<VideoJuego> VideoJuegoDAO::ObtenerVideoJuegos() {
	std::vector<VideoJuego> videojuegos;
	try {
		std::string query = "SELECT v.id_videojuego, v.nombre, c.id_categoria, c.nombre AS nombre_categoria "
			"FROM videojuego v "
			"JOIN categoria c ON v.id_categoria = c.id_categoria";
		auto [stmt, rs] = dbManager.executeQueryWithStatement(query);
		while (rs->next()) {
			VideoJuego juego = mapResultSet(rs.get());
			videojuegos.push_back(juego);
		}
	}
	catch (const sql::SQLException& e) {
		std::cerr << "Error fetching video games: " << e.what() << std::endl;
	}
	return videojuegos;
}


//