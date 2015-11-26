

#ifndef HANDLEREVENTOS_H_
#define HANDLEREVENTOS_H_

// Servidor
#include "Conexion.h"
#include "mongoose.h"
#include "Respuesta.h"
#include "../utiles/Log.h"

// STL
#include <string.h>
#include <sstream>

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
