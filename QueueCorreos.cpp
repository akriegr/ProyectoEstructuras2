#include "QueueCorreos.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <cstdlib>

using namespace std;

bool QueueCorreos::enviar(const Correo& correo) {
    // Crear script de PowerShell
    ofstream file("temp_mail.ps1");
    file << "$smtpServer='" << dataSMTP.servidor << "'\n"
        << "$smtpPort=" << dataSMTP.puerto << "\n"
        << "$username='" << dataSMTP.usuario << "'\n"
        << "$password='" << dataSMTP.contrasena << "'\n"
        << "$from='" << dataSMTP.usuario << "'\n"
        << "$to='" << correo.destinatario << "'\n"
        << "$subject='" << correo.asunto << "'\n"
        << "$body='" << correo.cuerpo << "'\n"
        << "$smtp=New-Object System.Net.Mail.SmtpClient($smtpServer,$smtpPort)\n"
        << "$smtp.EnableSsl=$true\n"
        << "$smtp.Credentials=New-Object System.Net.NetworkCredential($username,$password)\n"
        << "$mail=New-Object System.Net.Mail.MailMessage($from,$to,$subject,$body)\n"
        << "$smtp.Send($mail)\n";
    file.close();

    // Ejecutar PowerShell
    string cmd = "powershell -ExecutionPolicy Bypass -File temp_mail.ps1 2>nul";
    bool exito = (system(cmd.c_str()) == 0);

    // Limpiar
    remove("temp_mail.ps1");
    return exito;
}

void QueueCorreos::procesar() {
    while (ejecutando) {
        if (!colaCorreos.empty()) {
            Correo correo = colaCorreos.front();
            colaCorreos.pop();

            cout << "Enviando correo a: " << correo.destinatario << "... ";

            if (enviar(correo)) {
                cout << "Correo enviado!" << endl;
            }
            else {
                cout << "Error al enviar correo" << endl;
            }
        }
        else {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }
}

QueueCorreos::QueueCorreos(const DataSMTP& data)
    : dataSMTP(data), ejecutando(true) {
    hilo = thread(&QueueCorreos::procesar, this);
    cout << "Hilo iniciado" << endl;
}

QueueCorreos::~QueueCorreos() {
    ejecutando = false;
    if (hilo.joinable()) {
        hilo.join();
    }
    cout << "Hilo detenido" << endl;
}

void QueueCorreos::agregarCorreo(const Correo& correo) {
    colaCorreos.push(correo);
    cout << "Correo agregado: " << correo.asunto
        << " (cola: " << colaCorreos.size() << ")" << endl;
}

int QueueCorreos::pendientes() const {
    return colaCorreos.size();
}