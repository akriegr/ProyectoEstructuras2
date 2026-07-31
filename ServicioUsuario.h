#pragma once
#include "IUsuarioDAO.h"
#include "Usuario.h"
#include <memory>
using namespace std;

class ServicioUsuario {
private:
	unique_ptr<IUsuarioDAO> usuarioDAO;
public: 
	ServicioUsuario(unique_ptr<IUsuarioDAO> dao) : usuarioDAO(std::move(dao)) {}
	
	bool insertarUsuario(int cedula, string nombre, string contrasena, string correo) {
		return usuarioDAO->insertarUsuario(cedula, nombre, contrasena, correo);
	}

	vector<Usuario> obtenerTodosUsuarios() {
		return usuarioDAO->ObtenerUsuarios();
	}

	bool eliminarUsuario(int id) {
		return usuarioDAO->eliminarUsuario(id);
	}
	
	bool actualizarUsuario(int idUsuario, string nombreNuevo) {
		return usuarioDAO->actualizarUsuario(idUsuario, nombreNuevo);
	}
};
