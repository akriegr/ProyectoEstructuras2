#pragma once
#include "Categoria.h"
#include <vector>
#include <optional>
#include "DBManager.h"

class ICategoriaDAO {
	//interfaz de categoriaDAO, defino cuales operaciones se pueden hacer 
public:
	virtual ~ICategoriaDAO() = default;

	//Crud basico
	//virtual bool insertar(const Categoria& categoria) = 0;
	//virtual optional<Categoria> obtenerPorId(int id) = 0;
	virtual vector <Categoria>ObtenerCategorias() = 0;
	//virtual bool actualizar(const Categoria& categoria) = 0;
	//virtual bool eliminar(int id) = 0;	

	//Consultas adicionales


};
