#pragma once
#include "Usuario.h"
#include <vector>
#include <optional>
#include "DBManager.h"
using namespace std;

class IUsuarioDAO {
	//interfaz de usuarioDAO, defino cuales operaciones se pueden hacer
public:
	~IUsuarioDAO() = default;

	virtual bool insertarUsuario(int cedula, string nombre, string contrasena) = 0;
	virtual vector <Usuario>ObtenerUsuarios() = 0;
	virtual bool eliminarUsuario(int id) = 0;
	virtual bool actualizarUsuario(int idUsuario, string nombreNuevo) = 0;
};
