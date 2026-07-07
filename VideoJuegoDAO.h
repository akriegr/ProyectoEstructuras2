#pragma once
#include "IVideoJuegoDAO.h"
#include <mariadb/conncpp.hpp>
#include <memory>

class VideoJuegoDAO : public IVideoJuegoDAO {

private:
	DBManager& dbManager;
	VideoJuego mapResultSet(sql::ResultSet* rs);

public:
	VideoJuegoDAO(DBManager& manager);
	//virtual bool insertar(const VideoJuego& videojuego) override;
	//virtual optional<VideoJuego> obtenerPorId(int id) override;
	virtual vector <VideoJuego>ObtenerVideoJuegos() override;
	//virtual bool actualizar(const VideoJuego& videojuego) override;
	//virtual bool eliminar(int id) override;

};