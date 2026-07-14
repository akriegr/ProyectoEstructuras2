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
	vector<Usuario> obtenerTodosUsuarios() {
		return usuarioDAO->ObtenerUsuarios();
	}
};
