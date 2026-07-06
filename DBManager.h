#pragma once
#include <mariadb/conncpp.hpp>
#include <memory>
#include <string>

class DBManager {
	public:
		DBManager(const DBManager&) = delete;
		DBManager& operator=(const DBManager&) = delete;
		DBManager(DBManager&&) = delete;
		DBManager& operator=(DBManager&&) = delete;

		//metodo statico para accesa solo una instancia 
		static DBManager& getInstance();

		//metodos publicos para tener acceso a la operaciones de base de datos
		bool connect();
		void disconnect();
		bool isConnected() const;

		std::pair< std::unique_ptr<sql::Statement>,std::unique_ptr<sql::ResultSet>> executeQueryWithStatement(const std::string& query);
		int executeUpdate(const std::string& query);
		sql::Connection* getConnection() const { return conn_.get(); }

	private:
		//constructor privado
		DBManager();
		
		//declaracion de instancia estatica
		static DBManager* instance_;


		//metodo privado para las propiedades de mariadb
		void setProperties();

		//variables para la conexion a la base de datos
		std::unique_ptr<sql::Connection> conn_;
		sql::Driver* driver_;
		std::string url_;
		std::string user_;
		std::string password_;
		bool isConnected_;

};