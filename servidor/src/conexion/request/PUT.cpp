
#include "PUT.h"

using namespace ConexionServidor::Request;

PUT::PUT() {}

PUT::~PUT() {}

ConexionServidor::Respuesta PUT::ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenido, std::string query)
{
	return operacion->put(contenido, query);
}

std::string PUT::impresion()
{
	return std::string("PUT");
}
