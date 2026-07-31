#pragma once
#include <queue>
#include <string>
#include <thread>
#include <atomic>
#include "DataSMTP.h"

using namespace std;

struct Correo {
	string remitente;
	string destinatario;
	string asunto;
	string cuerpo;
};

class QueueCorreos {
private:
	queue<Correo> colaCorreos;
	atomic<bool>ejecutando;
	thread hilo;
	DataSMTP dataSMTP;

	bool enviar(const Correo& correo);
	void procesar();

	
public:
	QueueCorreos(const DataSMTP& dataSMTP);

	~QueueCorreos();

	void agregarCorreo(const Correo& correo);

	int pendientes() const;

};