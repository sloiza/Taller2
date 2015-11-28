

#include "GET.h"

using namespace ConexionServidor::Request;

GET::GET() {}

GET::~GET() {}

ConexionServidor::Respuesta GET::ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenido, std::string query)
{
	return operacion->get(contenido, query);
}

std::string GET::impresion()
{
	return std::string("GET");
}

