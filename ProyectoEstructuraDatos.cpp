#include <iostream>
#include "DBManager.h"
#include <memory>
#include "CategoriaDAO.h"
#include "ServicioCategoria.h"
#include "VideoJuegoDAO.h"
#include "ServicioVideoJuego.h"
#include "ArbolBPlus.h"
using namespace std;

//inlcuyo DAO y Servicio

ArbolBPlus arbolito;

void inicializarArbol() {
    try {
        auto& dbManager = DBManager::getInstance();
        ServicioVideoJuego servicioVideoJuego(make_unique < VideoJuegoDAO>(dbManager));
        vector<VideoJuego>listaVideoJuegos = servicioVideoJuego.obtenerTodosVideoJuegos();
        for (int i = 0;i < listaVideoJuegos.size(); i++) {
            arbolito.insertarVideoJuego(listaVideoJuegos[i]);
        }
        dbManager.disconnect();
    }
    catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
    }
}

int insertarVideoJuego(string nombre, int idCategoria) {
    try {
        auto& dbManager = DBManager::getInstance();
        ServicioVideoJuego servicioVideoJuego(std::make_unique < VideoJuegoDAO>(dbManager));
        
	    int resultado = servicioVideoJuego.insertarVideoJuego(nombre, idCategoria);

        return resultado;

        dbManager.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void imprimirCategorias() {
    try {
        auto& dbManager = DBManager::getInstance();
        ServicioCategoria servicioCategoria(make_unique <CategoriaDAO>(dbManager));
        vector<Categoria>listaCategorias = servicioCategoria.obtenerTodasCategorias();

        cout << "*****Lista de Categorias*****" << endl;

        for (int i = 0;i < listaCategorias.size(); i++) {
            cout << "ID: "<< listaCategorias[i].getId() << "Nombre: " << listaCategorias[i].getNombre() << endl;
        }
        dbManager.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool actualizarVideoJuego(int idVideoJuego, string nombreNuevo) {
    try {
        auto& dbManager = DBManager::getInstance();
        ServicioVideoJuego servicioVideoJuego(std::make_unique < VideoJuegoDAO>(dbManager));
        bool resultado = servicioVideoJuego.actualizarVideoJuego(idVideoJuego, nombreNuevo);
        return resultado;
        dbManager.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

Categoria obtenerCategoriaPorId(int id) {
	try {
		auto& dbManager = DBManager::getInstance();
		ServicioCategoria servicioCategoria(make_unique <CategoriaDAO>(dbManager));
		optional <Categoria> categoria = servicioCategoria.obtenerCategoriaPorId(id);
		dbManager.disconnect();
		return categoria.value();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return Categoria(); // Retorna una categoría vacía en caso de error
	}
}

int main() {

    inicializarArbol();

    int opcion = 0;
    while (opcion != 7) {
        cout << "****** Opciones ******" << endl;
        cout << "1. Listar Video Juegos" << endl;
        cout << "2. Buscar Video Juego" << endl;
        cout << "3. Eliminar Video Juego" << endl;
		cout << "4. Actualizar Video Juego" << endl;
		cout << "5. Insertar Video Juego" << endl;
        cout << "7. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                system("cls");
                arbolito.imprimir();
                system("pause");
                break;
            case 2: {
                system("cls");
                cout << "Digite el nombre del videojuego que desea buscar: ";
                string nombre;
                cin.ignore();
                getline(cin, nombre);

                VideoJuego* encontrado = arbolito.buscar(nombre);
                if (encontrado == nullptr) {
                    cout << "No se encontro el videojuego" << endl;
                }
                else {
                    cout << "Videojuego encontrado: " << endl;
                    cout << "ID: " << encontrado->getId() << endl;
                    cout << "Nombre: " << encontrado->getNombre() << endl;
                    cout << "Categoria: " << encontrado->getCategoria().getNombre() << endl;
                }
                system("pause");
                break;
                }
			case 3: {
				system("cls");
				/*cout << "Digite el nombre del videojuego que desea eliminar: ";
				string nombre;
				cin.ignore();
				getline(cin, nombre);
				bool eliminado = arbolito.eliminarVideoJuego(nombre);
				if (eliminado) {
					cout << "Videojuego eliminado exitosamente" << endl;
				}
				else {
					cout << "No se encontro el videojuego" << endl;
				}*/
                bool eliminado = arbolito.eliminarVideoJuego("WORLD OF WARCRAFT");
                if (eliminado) {
					cout << "VideoJuego eliminado exitosamente" << endl;
                }
                else {
					cout << "No se encontro el videojuego" << endl;
                }
				system("pause");
				break;
			}
            case 4: {
                system("cls");
                arbolito.imprimir();
                string nombre;
                string nuevoNombre;
                cout << "\n" << endl;
                cout << "Digite el nombre del videojuego que desea editar."<<endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, nombre);
                VideoJuego* videoJuego = arbolito.buscar(nombre);

                if (videoJuego != nullptr) {
                    cout << "Digite el nuevo nombre: " << endl;
                    getline(cin, nuevoNombre);
                    bool actualizado = actualizarVideoJuego(videoJuego->getId(), nuevoNombre);
                    if (actualizado) {

                        arbolito.actualizarVideoJuego(nombre, nuevoNombre);
                        cout << "VideoJuego actualizado exitosamente" << endl;
                    }
                    else {
                        cout << "No se encontro el videojuego" << endl;
                    }
                }
                else {
                    cout << "No se encontro el videojuego" << endl;
                }
                break;
                system("pause");
            }
            case 5: {
				system("cls");
                imprimirCategorias();

				int idCategoria;
				string nombre;

                cout << "Digite el ID de la categoria deseada" << endl;
                cin >> idCategoria;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

				Categoria categoria = obtenerCategoriaPorId(idCategoria);
				cout << "Digite el nombre del videojuego: ";
                getline(cin, nombre);

				int idVideojuego = insertarVideoJuego(nombre, idCategoria);
                if (idVideojuego == -1) {
                    cout << "Error al crear VideoJuego" << endl;
                    break;
                }
                else {
                    VideoJuego videojuego = VideoJuego(idVideojuego, nombre, categoria);

                    arbolito.insertarVideoJuego(videojuego);

                    cout << "VideoJuego insertado exitosamente!" << endl;
                }

				system("pause");
                break;
            }

            case 7: {
                cout << "Saliendo del programa..." << endl;
                break;
            }
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }
}