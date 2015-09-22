/*
 * HandlerEventos.cpp
 *
 *  Created on: 17/9/2015
 *      Author: manuel
 */

#include "HandlerEventos.h"

using namespace ConexionServidor;

HandlerEventos::HandlerEventos()
{
}
HandlerEventos::~HandlerEventos()
{
}

int HandlerEventos::handler(struct mg_connection *conn, enum mg_event ev)
{
	//Conexion* conexion = new Conexion(conn);
	static const char *s_no_cache_header =
	  "Cache-Control: max-age=0, post-check=0, "
	  "pre-check=0, no-store, no-cache, must-revalidate\r\n";

	switch(ev)
	{
		case MG_AUTH: return MG_TRUE;
		case MG_REQUEST:
		  mg_printf_data(conn, "Hello! Requested URI is [%s]\n", conn->uri);
		  return MG_TRUE;
//			Respuesta rta = procesarRequest(conexion);
//			return rta.getResultado();
		default: return MG_FALSE;
	}
}
