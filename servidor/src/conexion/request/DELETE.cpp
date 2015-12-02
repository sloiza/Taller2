

#include "DELETE.h"

using namespace ConexionServidor::Request;

DELETE::DELETE() {}

DELETE::~DELETE() {}

ConexionServidor::Respuesta DELETE::ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenido, std::string query)
{
	return operacion->delet(contenido, query);
}


std::string DELETE::impresion()
{
	return std::string("DELETE");
}

