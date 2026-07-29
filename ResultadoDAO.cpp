#include "ResultadoDAO.h"
#include "UsuarioDAO.h"
#include "JuegoDAO.h"
#include <iostream>
#include <sstream>

ResultadoDAO::ResultadoDAO(DBManager& dbManager) : dbManager(dbManager) {
	if (!dbManager.isConnected()) {
		dbManager.connect();
	}
}

Resultado ResultadoDAO::mapResultSet(sql::ResultSet* rs) {
	int idResultado = rs->getInt("id_resultado");
	int puntos = rs->getInt("puntos");
	int ganadoSql = rs->getInt("ganado");
	bool ganado;
	if (ganadoSql == 1) {
		ganado = true;
	}
	else {
		ganado = false;
	}
	//creo objeto videojuego
	int idVideoJuego = rs->getInt("id_videojuego");
	string nombreVideoJuego = rs->getString("nombre_videojuego").c_str();
	int idCategoria = rs->getInt("id_categoria");
	string nombreCategoria = rs->getString("nombre_categoria").c_str();
	Categoria categoria(idCategoria, nombreCategoria);
	VideoJuego videojuego(idVideoJuego, nombreVideoJuego, categoria);
	//Creo objeto juego
	int idJuego = rs->getInt("id_juego");
	string fecha = rs->getString("fecha").c_str();
	Juego juego(idJuego, fecha, videojuego);
	//creo objeto usuario 
	int cedula = rs->getInt("cedula");
	string nombre = rs->getString("nombre_usuario").c_str();
	string contrasena = rs->getString("contrasena").c_str();
	Usuario usuario(cedula, nombre, contrasena);

	return Resultado(idResultado,puntos,ganado,juego,usuario);
}

bool ResultadoDAO::insertar(int puntos, bool ganado, int idJuego, int cedula) {
	try {
		string query = "INSERT INTO RESULTADO(puntos,ganado,id_juego,cedula_usuario) VALUES (" +
			to_string(puntos) + "," + to_string(ganado ? 1 : 0) + "," + to_string(idJuego) + "," + to_string(cedula) + ")";
		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);
		delete stmt;
		return filasAfectadas > 0; // Devuelve true si se insertó al menos una fila
		return true;
	}
	catch (sql::SQLException& e) {
		cerr << "Error inserting game: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}

vector<Resultado> ResultadoDAO::obtenerResultados() {
	vector<Resultado> resultados;
	try {
		string query = "SELECT r.id_resultado, r.puntos, r.ganado, "
			"j.id_juego, j.fecha, "
			"v.id_videojuego, v.nombre AS nombre_videojuego, "
			"c.id_categoria, c.nombre AS nombre_categoria, "
			"u.cedula, u.nombre AS nombre_usuario, u.contrasena "
			"FROM resultado r "
			"INNER JOIN juego j ON r.id_juego = j.id_juego "
			"INNER JOIN videojuego v ON j.id_videojuego = v.id_videojuego "
			"INNER JOIN categoria c ON v.id_categoria = c.id_categoria "
			"INNER JOIN usuario u ON r.cedula_usuario = u.cedula";
		auto [stmt, rs] = dbManager.executeQueryWithStatement(query);
		while (rs->next()) {
			Resultado resultado= mapResultSet(rs.get());
			resultados.push_back(resultado);
		}
	}
	catch (const sql::SQLException& e) {
		cerr << "Error retrieving games: " << e.what() << std::endl;
	}
	return resultados;
}

bool ResultadoDAO::actualizar(int idResultado, int puntosActualizados) {
	try {
		string query = "UPDATE RESULTADO SET puntos = " + to_string(puntosActualizados) +
			" WHERE id_resultado = " + to_string(idResultado);
		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);
		delete stmt;
		return filasAfectadas > 0; // Devuelve true si se actualizó al menos una fila
	}
	catch (sql::SQLException& e) {
		cerr << "Error updating game: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}

bool ResultadoDAO::eliminar(int idResultado) {
	try {
		string query = "DELETE FROM RESULTADO WHERE id_resultado = " + to_string(idResultado);
		sql::Statement* stmt = dbManager.getConnection()->createStatement();
		int filasAfectadas = stmt->executeUpdate(query);
		delete stmt;
		return filasAfectadas > 0; // Devuelve true si se eliminó al menos una fila
	}
	catch (sql::SQLException& e) {
		cerr << "Error deleting game: " << e.what() << std::endl;
		return false; // Error de SQL
	}
}