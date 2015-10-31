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

int HandlerEventos::handler(struct mg_connection* conn, enum mg_event ev)
{
	switch(ev)
	{
		case MG_AUTH: return MG_TRUE;
		case MG_REQUEST:
		{
			Conexion* conexion = new Conexion();
			conexion->inicializar(conn);

			mg_printf_data(conn, conexion->impresion().c_str());

			Utiles::Log::instancia()->info( std::string("\nConexion recibida:\n") + conexion->impresion(), std::string("HandlerEventos"));

//			Respuesta rta = procesarRequest(conexion);
//			switch( rta.getResultado() )
//			  {
//				  HAY_RESPUESTA: return MG_TRUE;
//				  NO_HAY_RESPUESTA: return MG_FALSE;
//				  FALTA_COMPLETAR_RESPUESTA: return MG_MORE;
//			  }

			delete conexion;
		  return MG_TRUE;
		}

		default: return MG_FALSE;
	}
}
