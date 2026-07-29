#include "JuegoDAO.h"
#include "VideoJuegoDAO.h"
#include <iostream>
#include <sstream>
using namespace std;

JuegoDAO::JuegoDAO(DBManager& dbManager) : dbManager(dbManager) {
	if (!dbManager.isConnected()) {	
		dbManager.connect();
	}
}

Juego JuegoDAO::mapResultSet(sql::ResultSet* rs) {
	int idJuego = rs->getInt("id_juego");
	string fecha = rs->getString("fecha").c_str();
	int idVideoJuego = rs->getInt("id_videojuego");
	string nombreVideoJuego = rs->getString("nombre_videojuego").c_str();
	int idCategoria = rs->getInt("id_categoria");
	string nombreCategoria = rs->getString("nombre_categoria").c_str();
	Categoria categoria(idCategoria, nombreCategoria);
	VideoJuego videojuego(idVideoJuego, nombreVideoJuego, categoria);
	return Juego(idJuego, fecha, videojuego);
}

//CRUD
//create

bool JuegoDAO::insertar(const string fecha, int idVideoJuego) {
	try {
		string query = "INSERT INTO juego(fecha, id_videojuego) VALUES ('" +
			fecha + "'," + to_string(idVideoJuego) + ")";
		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);
		delete stmt;
		return filasAfectadas > 0; // Devuelve true si se insertó al menos una fila
	}
	catch (const sql::SQLException& e) {
		cerr << "Error inserting game: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}

//READ

vector<Juego>JuegoDAO::obtenerJuegos() {
	vector<Juego> juegos;
	try {
		string query = "SELECT j.id_juego, j.fecha, v.id_videojuego, v.nombre AS nombre_videojuego, c.id_categoria, c.nombre AS nombre_categoria "
			"FROM juego j "
			"JOIN videojuego v ON j.id_videojuego = v.id_videojuego "
			"JOIN categoria c ON v.id_categoria = c.id_categoria";
		auto [stmt,rs] = dbManager.executeQueryWithStatement(query);
		while (rs->next()) {
			Juego juego = mapResultSet(rs.get());
			juegos.push_back(juego);
		}
	}
	catch (const sql::SQLException& e) {
		cerr << "Error retrieving games: " << e.what() << std::endl;
	}
	return juegos;
}

//UPDATE
bool JuegoDAO::actualizar(int idJuego, const string nuevaFecha) {
	try {
		string query = "UPDATE juego SET fecha = '" + nuevaFecha +
			" WHERE id_juego = " + to_string(idJuego);
		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);
		delete stmt;
		return filasAfectadas > 0; // Devuelve true si se actualizó al menos una fila
	}
	catch (const sql::SQLException& e) {
		cerr << "Error updating game: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}

//DELeTE 

bool JuegoDAO::eliminar(int idJuego) {
	try {
		string query = "DELETE FROM juego WHERE id_juego = " + to_string(idJuego);
		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);
		delete stmt;
		return filasAfectadas > 0; // Devuelve true si se eliminó al menos una fila
	}
	catch (const sql::SQLException& e) {
		cerr << "Error deleting game: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}

