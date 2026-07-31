#include <iostream>
#include "DBManager.h"
#include <memory>
#include "CategoriaDAO.h"
#include "ServicioCategoria.h"
#include "VideoJuegoDAO.h"
#include "ServicioVideoJuego.h"
#include "ArbolBPlus.h"
#include "UsuarioDAO.h"
#include "ServicioUsuario.h"
#include "ArbolRN.h"
#include "JuegoDAO.h"
#include "ServicioJuego.h"
#include "ResultadoDAO.h"
#include "ServicioResultado.h"
#include "TablaHash.h"
#include "QueueCorreos.h"
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

//inlcuyo DAO y Servicio

ArbolBPlus arbolito;
ArbolRN arbolitoRN;
TablaHash tablita;
DataSMTP dataSMTP;
QueueCorreos cola(dataSMTP);

string obtenerFecha() {
    time_t now = time(0);
    struct tm localTime;
    localtime_s(&localTime, &now);  // Windows: localtime_s
    //hacer fecha YYYY-MM-DD
    char buffer[11];  // "YYYY-MM-DD" + null terminator
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &localTime);
    return string(buffer);
}

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

bool eliminarVideoJuego(int id) {
	try {
		auto& dbManager = DBManager::getInstance();
		ServicioVideoJuego servicioVideoJuego(std::make_unique < VideoJuegoDAO>(dbManager));
		bool resultado = servicioVideoJuego.eliminarVideoJuego(id);
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

void inicializarArbolRN() {
    try {
        auto& dbManager = DBManager::getInstance();
        ServicioUsuario servicioUsuario(make_unique <UsuarioDAO>(dbManager));
        vector<Usuario>listaUsuarios = servicioUsuario.obtenerTodosUsuarios();

        for (int i = 0;i < listaUsuarios.size(); i++) {
			arbolitoRN.insertar(listaUsuarios[i]);
        }
        dbManager.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool eliminarUsuario(int id) {
	try {
		auto& dbManager = DBManager::getInstance();
		ServicioUsuario servicioUsuario(std::make_unique < UsuarioDAO>(dbManager));
		bool resultado = servicioUsuario.eliminarUsuario(id);
		return resultado;
		dbManager.disconnect();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

bool actualizarUsuario(int idUsuario, string nombreNuevo) {
	try {
		auto& dbManager = DBManager::getInstance();
		ServicioUsuario servicioUsuario(std::make_unique < UsuarioDAO>(dbManager));
		bool resultado = servicioUsuario.actualizarUsuario(idUsuario, nombreNuevo);
		return resultado;
		dbManager.disconnect();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

bool insertarUsuario(int cedula, string nombre, string contrasenna,string correo) {
	try {
		auto& dbManager = DBManager::getInstance();
		ServicioUsuario servicioUsuario(std::make_unique < UsuarioDAO>(dbManager));
		bool resultado = servicioUsuario.insertarUsuario(cedula, nombre, contrasenna,correo);
		return resultado;
		dbManager.disconnect();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void imprimirJuegos() {
    try {
        auto& dbManager = DBManager::getInstance();
        ServicioJuego servicioJuego(make_unique <JuegoDAO>(dbManager));
        vector<Juego>listaJuegos = servicioJuego.obtenerJuegos();
        for (const auto& juego : listaJuegos) {
            cout << "ID: " << juego.getId() << ", Fecha: " << juego.getFecha()<<" VideoJuego: " << juego.getVideoJuego().getNombre() << endl;
        }
        dbManager.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool insertarJuego(int idVideoJuego) {
	try {
		auto& dbManager = DBManager::getInstance();
		string fecha = obtenerFecha();
		ServicioJuego servicioJuego(std::make_unique<JuegoDAO>(dbManager));
		bool resultado = servicioJuego.insertarJuego(fecha, idVideoJuego);
		return resultado;
		dbManager.disconnect();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

void incializarTablaHash() {
    try {
        auto& dbManager = DBManager::getInstance();
        ServicioResultado servicioResultado(make_unique <ResultadoDAO>(dbManager));
        vector<Resultado>listaResultados = servicioResultado.obtenerResultados();
        for (const auto& resultado : listaResultados) {
			tablita.insertar(resultado);
        }
        dbManager.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void enviarCorreoJuegoCreado(Usuario usuario) {

	if (usuario.getCorreo().empty()) {
		cout << "El usuario no tiene correo electrónico registrado." << endl;
		return;
	}

    Correo correo;
    correo.remitente = dataSMTP.usuario;
    correo.destinatario = usuario.getCorreo();
    correo.asunto = "Juego Creado";
    correo.cuerpo = "Se ha creado un nuevo juego. ¡Disfrútalo!";
    cola.agregarCorreo(correo);
}

int main() {

    inicializarArbol();
    inicializarArbolRN();
    incializarTablaHash();
    

    int opcion = 0;
    while (opcion != 20) {
		system("cls");
        cout << "****** Opciones ******" << endl;
        cout << "1. Listar Video Juegos" << endl;
        cout << "2. Buscar Video Juego" << endl;
        cout << "3. Eliminar Video Juego" << endl;
		cout << "4. Actualizar Video Juego" << endl;
		cout << "5. Insertar Video Juego" << endl;
		cout << "6. Listar Usuarios" << endl;
        cout << "7. Buscar Usuario por Nombre" << endl;
        cout << "8. Eliminar Usuario" << endl;
        cout << "9. Actualizar Usuario" << endl;
        cout << "10. Insertar Usuario" << endl;
		cout << "11. Listar Juegos" << endl;
		cout << "12. Crear Juego" << endl;
		cout << "13. Listar Resultados" << endl;
        cout << "14. Buscar Resultado" << endl;
        cout << "15 Enviar Correo" << endl;
        cout << "20. Salir" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:{
                system("cls");
                arbolito.imprimir();
                system("pause");
                break;
            }
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
                string nombre;
                arbolito.imprimir();
				
                cout << "\n" << endl;
                
                cout << "Digite el nombre del videojuego que desea eliminar: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, nombre);

				VideoJuego* encontrado = arbolito.buscar(nombre);

                if (encontrado != nullptr) {
                    bool eliminado = eliminarVideoJuego(encontrado->getId());
                    if (eliminado) {
						arbolito.eliminarVideoJuego(nombre);
						cout << "VideoJuego eliminado exitosamente" << endl;
                    }
                    else {
						cout << "No se pudo eliminar el videojuego" << endl;
                    }
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
			case 6: {
				system("cls");
                arbolitoRN.imprimir();
				system("pause");
				break;
			}
            case 7: {
                system("cls");
                string nombre;
                cout << "Digite el nombre de usuario que desea buscar: "<<endl;
				cin >> nombre;
                Usuario* usuarioEncontrado = arbolitoRN.buscar(nombre);
                if (usuarioEncontrado != nullptr) {
					cout << "Usuario encontrado: " << endl;
					cout << "Correo: " << usuarioEncontrado->getCorreo() << endl;
					cout << "Cedula: " << usuarioEncontrado->getCedula() << endl;
                    cout << "Nombre: " << usuarioEncontrado->getNombre() << endl;
                }
                else {
					cout << "Usuario no existe" << endl;
                }
				system("pause");
                break;
            }
            case 8: {
                system("cls");
                string nombre;
                arbolitoRN.imprimir();
				cout << "\n" << endl;
                cout << "Digite el nombre de usuario que desea eliminar: " << endl;
                cin >> nombre;
				Usuario* usuarioEncontrado = arbolitoRN.buscar(nombre);
				if (usuarioEncontrado != nullptr) {
					bool eliminado = eliminarUsuario(usuarioEncontrado->getCedula());
					if (eliminado) {
						arbolitoRN.eliminar(nombre);
						cout << "Usuario eliminado exitosamente" << endl;
					}
					else {
						cout << "No se pudo eliminar el usuario" << endl;
					}
				}
				else {
					cout << "Usuario no existe" << endl;
				}
                system("pause");
                break;
            }
            case 9: {
                system("cls");
                arbolitoRN.imprimir();
                string nombre;
                string nuevoNombre;
                cout << "\n" << endl;
                cout << "Digite el nombre del usuario que desea editar." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, nombre);
				Usuario* usuarioEncontrado = arbolitoRN.buscar(nombre);
				if (usuarioEncontrado != nullptr) {
					cout << "Digite el nuevo nombre: " << endl;
					getline(cin, nuevoNombre);
					bool actualizado = actualizarUsuario(usuarioEncontrado->getCedula(), nuevoNombre);
					if (actualizado) {
						arbolitoRN.actualizarNombre(nombre,nuevoNombre);

						cout << "Usuario actualizado exitosamente" << endl;
					}
					else {
						cout << "No se encontro el usuario" << endl;
					}
				}
				else {
					cout << "No se encontro el usuario" << endl;
				}
				system("pause");
				break;
            }
            case 10: {
				system("cls");
				string nombre;
				int cedula;
                string contrasena;
                string correo;
				cout << "Digite el numero de cedula del usuario: " << endl;
				cin >> cedula;
                cout << "Digite el nombre del usuario que desea crear: " << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin, nombre);
				cout << "Digite la contrasena del usuario: " << endl;
                getline(cin, contrasena);
                cout << "Digite el correo del usuario: " << endl;
                getline(cin, correo);
				bool creado = insertarUsuario(cedula, nombre, contrasena,correo);
                if (creado) {
					arbolitoRN.insertar(Usuario(cedula, nombre, contrasena,correo));
					cout << "Usuario creado exitosamente!" << endl;
                }
                else {
					cout << "Error al crear usuario" << endl;
                }
                system("pause");
                break;
            }
            case 11: {
                system("cls");
				imprimirJuegos();
				system("pause");
                break;
            }
            case 12: {
                system("cls");
                int idVideojuego = 0;

				cout << "Digite el ID del videojuego del juego: " << endl;
				cin >> idVideojuego;

				bool insertado = insertarJuego(idVideojuego);

                if (insertado) {
					cout << "Juego insertado exitosamente!" << endl;
                }else{
					cout << "Error al insertar el juego" << endl;
				}
				system("pause");

                break;
            }
            case 13: {
                system("cls");

                tablita.verResultados();

                system("pause");
                break;
            }
            case 14: {
                system("cls");

                tablita.verResultados();
                cout << "Digite el id del resultado que desea ver:" << endl;
                int idResultado; 
                cin >> idResultado;

                Resultado* resultadoEncontrado = tablita.buscar(idResultado);
                string ganado; 

                if (resultadoEncontrado->isGanado()) {
                    ganado = "Si";
                }
                else {
                    ganado = "No";
                }

                cout << "Resultado: " << endl;
                cout << "FECHA: " << resultadoEncontrado->getJuego().getFecha() << endl;
				cout << "VIDEOJUEGO: " << resultadoEncontrado->getJuego().getVideoJuego().getNombre() << endl;
				cout << "PUNTOS: " << resultadoEncontrado->getPuntos() << endl;
                cout << "GANADO: " << ganado << endl;
                cout << "USUARIO: " << resultadoEncontrado->getUsuario().getNombre() << endl;
				system("pause");
				break;
            }
            case 15: {
                Correo correitoTest;
                Correo correitoTest2;
                correitoTest.remitente = "test@gmail.com";
                correitoTest.destinatario = "toonyk98@gmail.com";
                correitoTest.asunto = "Ojala esto sirva";
                correitoTest.cuerpo = "Esto sirvio aleluya";
                correitoTest2.remitente = "test@gmail.com";
                correitoTest2.destinatario = "toonyk98@gmail.com";
                correitoTest2.asunto = "Test 2";
                correitoTest2.cuerpo = "Esto sirvio aleluya 2";
                cola.agregarCorreo(correitoTest);
                cola.agregarCorreo(correitoTest2);

                this_thread::sleep_for(chrono::seconds(10));

                cout << "Correos Restantes: " << cola.pendientes() << endl;



            }
            case 20:
				cout << "Saliendo del programa..." << endl;
				break;
            default:
                cout << "Opcion no valida" << endl;
                break;
        }
    }
}