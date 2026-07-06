#include <iostream>
#include "DBManager.h"
#include <memory>
#include "CategoriaDAO.h"
#include "ServicioCategoria.h"

//inlcuyo DAO y Servicio

int main() {
    try {
        auto& dbManager = DBManager::getInstance();

        if (dbManager.connect()) {
            std::cout << "Connected to the database successfully!" << std::endl;
        }

		ServicioCategoria servicioCategoria(std::make_unique<CategoriaDAO>(dbManager));
        vector<Categoria> listaCategoria= servicioCategoria.obtenerTodasCategorias();
		for (int i = 0; i < listaCategoria.size(); i++) {
			std::cout << "ID: " << listaCategoria[i].getId() << ", Nombre: " << listaCategoria[i].getNombre() << std::endl;
		}

        dbManager.disconnect();
    }
    catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
