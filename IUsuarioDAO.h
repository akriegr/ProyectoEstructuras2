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

	virtual vector <Usuario>ObtenerUsuarios() = 0;
};
