/*
 * HandlerEventos.h
 *
 *  Created on: 17/9/2015
 *      Author: manuel
 */

#ifndef HANDLEREVENTOS_H_
#define HANDLEREVENTOS_H_

// STL
#include <string.h>
#include <sstream>

// Servidor
#include "Conexion.h"
#include "mongoose.h"
#include "../utiles/Log.h"

#include "../database/rocks_db.h"

using namespace std;
namespace ConexionServidor
{

class HandlerEventos
{
public:
	HandlerEventos();
	virtual ~HandlerEventos();

	static int handler(struct mg_connection *conn, enum mg_event ev);

private:


};
};

#endif /* HANDLEREVENTOS_H_ */
