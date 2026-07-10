#include <iostream>
#include "DBManager.h"
#include <memory>
#include "CategoriaDAO.h"
#include "ServicioCategoria.h"
#include "VideoJuegoDAO.h"
#include "ServicioVideoJuego.h"
#include "ArbolBPlus.h"

//inlcuyo DAO y Servicio

int main() {

    ArbolBPlus arbolito;

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

        ServicioVideoJuego servicioVideoJuego(std::make_unique < VideoJuegoDAO>(dbManager));

        vector<VideoJuego>listaVideoJuegos = servicioVideoJuego.obtenerTodosVideoJuegos();
        for (int i = 0;i < listaVideoJuegos.size(); i++) {
			arbolito.insertar(listaVideoJuegos[i]);
            
            //std::cout << "ID: " << listaVideoJuegos[i].getId() << ", Nombre: " << listaVideoJuegos[i].getNombre() << ",Categoria: " << listaVideoJuegos[i].getCategoria().getNombre()<<std::endl;
        }

		arbolito.imprimir();    

		/*cout << "Digite el id de la categoria que desea buscar: ";
		int opcion = 0;
		cin >> opcion;
		std::optional<Categoria> categoriEncontrada = servicioCategoria.obtenerCategoriaPorId(opcion);
		cout << "Categoria encontrada: " << categoriEncontrada->getNombre() << endl;
        */
        dbManager.disconnect();
    }
    catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
