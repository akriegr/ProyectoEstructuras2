#pragma once
#include <string>
#include "VideoJuego.h"
using namespace std;

class Juego {
private:
    int idJuego;
    string fecha;
    VideoJuego videojuego;

public:
    Juego() : idJuego(0), fecha("") {}
    Juego(int idJuego, string fecha, VideoJuego videojuego) : idJuego(idJuego), fecha(fecha), videojuego(videojuego) {};

    int getId()const { return idJuego; }
    void setId(int idJuego) { this->idJuego = idJuego; }

    string getFecha() const { return fecha; }
    void setFecha(const string& fecha) { this->fecha = fecha; }

    VideoJuego getVideoJuego()const { return videojuego; }
    void setVideoJuego(VideoJuego videojuego) { this->videojuego = videojuego; }

};
