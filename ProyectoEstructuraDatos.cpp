#include <iostream>
#include "DBManager.h"
#include <memory>
#include "CategoriaDAO.h"
#include "ServicioCategoria.h"
#include "VideoJuegoDAO.h"
#include "ServicioVideoJuego.h"
#include "ArbolBPlus.h"

//inlcuyo DAO y Servicio

ArbolBPlus arbolito;

void inicializarArbol() {
    try {
        auto& dbManager = DBManager::getInstance();
        ServicioVideoJuego servicioVideoJuego(std::make_unique < VideoJuegoDAO>(dbManager));
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

int main() {

    inicializarArbol();

    int opcion = 0;
    while (opcion != 7) {
        cout << "****** Opciones ******" << endl;
        cout << "1. Listar Video Juegos" << endl;
        cout << "2. Buscar Video Juego" << endl;
        cout << "3. Eliminar Video Juego" << endl;
		cout << "4. Actualizar Video Juego" << endl;
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
                string nuevoNombre = "WORLD OF WARCRAFT ACT";
                bool actualizado = arbolito.actualizarVideoJuego("WORLD OF WARCRAFT", nuevoNombre);

                if (actualizado) {
                    cout << "VideoJuego actualizado exitosamente" << endl;
                }
                else {
                    cout << "No se encontro el videojuego" << endl;
                }
                break;
                system("pause");
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