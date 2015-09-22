/*
 * Servidor.h
 *
 *  Created on: 16/9/2015
 *      Author: manuel
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

// STL
#include <iostream>
#include <signal.h>

// Conexion
#include "HandlerEventos.h"
#include "mongoose.h"
#include "../utiles/utiles.h"

namespace ConexionServidor
{

class Servidor
{
public:
	Servidor();
	virtual ~Servidor();

	void crear();
	void crear(int puerto);
	void setPuerto(int);
	void setOpcion(std::string nombre, std::string valor);
	void correr(int);
	bool estaCorriendo();
	void destruir();

protected:
	static void handlerSenial(int);

private:
	struct mg_server* servidorMG;
	int puerto;
	HandlerEventos handler;
	static bool corriendo;
};

};

#endif /* SERVIDOR_H_ */
