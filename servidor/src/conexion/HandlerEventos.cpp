/*
 * HandlerEventos.cpp
 *
 *  Created on: 17/9/2015
 *      Author: manuel
 */

#include "HandlerEventos.h"

using namespace ConexionServidor;
using namespace Utiles;

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
			rocks_db* rocks = new rocks_db();
			conexion->inicializar(conn);

			string json = "{\"firstName\":\"Samanta\",\"lastName\":\"Loiza\",\"nickName\":\"\",\"email\":\"samiloiza@gmail.com\",\"location\":\"Argentina\",\"id\":\"0\"}";
			int le = json.length();	
			const void * data = json.c_str();
			conexion->sendData(conn, data, le);

			conexion->procesarRequest();
			/* Test insert in db params from get */
			// string que= Utiles::parseQuery(conexion->getQuery());
			// cout <<  que << endl;
			// rocks->put("user", Slice("p"), que);
			// string val;
			// rocks->get("user", Slice("p"), &val);
			// cout << "value: " << val << endl;
			/* Test insert in db params from get */

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
