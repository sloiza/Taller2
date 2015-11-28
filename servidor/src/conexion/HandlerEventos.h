/// \file HandlerEventos.h
/// \date 2015-11-26
/// \brief Clase que contiene el metodo handler que utiliza mongoose.
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
/// \brief Clase que contiene el metodo handler que utiliza mongoose.
class HandlerEventos
{
public:
	/// \brief Constructor.
	HandlerEventos();
	/// \brief Destructor.
	virtual ~HandlerEventos();

	/// \brief Handler que utiliza mongoose para manejar las request.
	static int handler(struct mg_connection *conn, enum mg_event ev);

private:


};
};

#endif /* HANDLEREVENTOS_H_ */
