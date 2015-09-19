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

// Servidor
#include "mongoose.h"

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

} /* namespace Servidor */

#endif /* HANDLEREVENTOS_H_ */
