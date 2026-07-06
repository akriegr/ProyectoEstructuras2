#pragma once
#include "ICategoriaDAO.h"
#include "Categoria.h"
#include <memory>

class ServicioCategoria {

private: 
	std::unique_ptr<ICategoriaDAO> categoriaDAO;
public: 
	ServicioCategoria(std::unique_ptr<ICategoriaDAO> dao) : categoriaDAO(std::move(dao)) {}
	
	//metodos para interactuar con la bd
	/*/bool insertarCategoria(const Categoria& categoria) {
		return categoriaDAO->insertar(categoria);
	}
	std::optional<Categoria> obtenerCategoriaPorId(int id) {
		return categoriaDAO->obtenerPorId(id);
	}
	bool actualizarCategoria(const Categoria& categoria) {
		return categoriaDAO->actualizar(categoria);
	}
	bool eliminarCategoria(int id) {
		return categoriaDAO->eliminar(id);
	}*/
	std::vector<Categoria> obtenerTodasCategorias() {
		return categoriaDAO->ObtenerCategorias();
	}
};