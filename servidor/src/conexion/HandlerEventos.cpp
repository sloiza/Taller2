

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

			Utiles::Log::instancia()->info( std::string("\nConexion recibida:\n") + conexion->impresion(), std::string("HandlerEventos"));

			ConexionServidor::Respuesta respuesta = conexion->procesarRequest();

			// si se esta recuperando el usuario, entonces evito imprimir los datos para q no me imprima el string que contiene los bytes
			// de la imagen.
			if ( !(conexion->getUri()->getURI().compare("/usuario") == 0 && conexion->getMetodo()->impresion().compare("GET") == 0) &&
					conexion->getUri()->getURI().compare("/descargar") != 0)
				std::cout << "respuesta:\n" << respuesta.getContenido() << "\n";

			if ( respuesta.getEsDescarga() )
			{
				//mg_send_file(conn, respuesta.getPathDelArchivoADescargar().c_str(), NULL);
				mg_printf_data(conn, respuesta.getBytes().c_str());
				delete conexion;
				//return MG_MORE;
				return MG_TRUE;
			}
			else
			{
				mg_printf_data(conn, respuesta.getContenido().c_str());
				delete conexion;
				return MG_TRUE;
			}
		}
		case MG_CLOSE: return MG_TRUE;

		default: return MG_FALSE;
	}
}
