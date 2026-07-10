#include "VideoJuegoDAO.h"
#include "CategoriaDAO.h"
#include <iostream>
#include <sstream>
using namespace std;

VideoJuegoDAO::VideoJuegoDAO(DBManager& manager) : dbManager(manager) {
	if (!dbManager.isConnected()) {
		dbManager.connect();
	}
}

//metodo para mapear result a videojuego
VideoJuego VideoJuegoDAO::mapResultSet(sql::ResultSet* rs) {
	int id = rs->getInt("id_videojuego");
	string nombre = rs->getString("nombre").c_str();
	int id_categoria = rs->getInt("id_categoria");
	string nombre_categoria = rs->getString("nombre_categoria").c_str();
	Categoria categoria(id_categoria, nombre_categoria);
	return VideoJuego(id, nombre, categoria);
}

//CRUD

//CREATE

int VideoJuegoDAO::insertar(string nombre, int idCategoria) {
	try {
		string query = "INSERT INTO videojuego(nombre, id_categoria) VALUES ('" +
			nombre + "'," + to_string(idCategoria) + ")";

		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);

		if (filasAfectadas > 0) {
			// Obtener el ID generado automáticamente
			sql::ResultSet* rs = stmt->executeQuery("SELECT LAST_INSERT_ID()");
			int idGenerado = -1;
			if (rs->next()) {
				idGenerado = rs->getInt(1);
			}
			delete rs;
			delete stmt;
			return idGenerado; // devuelvo el id insertado
		}
		else {
			delete stmt;
			return -1; // Error: no se insertó ninguna fila
		}
	}
	catch (const sql::SQLException& e) {
		cerr << "Error inserting video game: " << e.what() << std::endl;
		return -1; // Error de SQL
	}
}




//READ

vector<VideoJuego> VideoJuegoDAO::ObtenerVideoJuegos() {
	vector<VideoJuego> videojuegos;
	try {
		string query = "SELECT v.id_videojuego, v.nombre, c.id_categoria, c.nombre AS nombre_categoria "
			"FROM videojuego v "
			"JOIN categoria c ON v.id_categoria = c.id_categoria";
		auto [stmt, rs] = dbManager.executeQueryWithStatement(query);
		while (rs->next()) {
			VideoJuego juego = mapResultSet(rs.get());
			videojuegos.push_back(juego);
		}
	}
	catch (const sql::SQLException& e) {
		cerr << "Error fetching video games: " << e.what() << std::endl;
	}
	return videojuegos;
}


//