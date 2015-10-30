/*
 * Conexion.cpp
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#include "Conexion.h"

using namespace ConexionServidor;

Conexion::Conexion() : uri(NULL), metodo(NULL), mapaMetodos(NULL) {}

Conexion::~Conexion()
{
	if ( uri != NULL )
	{
		delete uri;
	}

	if ( metodo != NULL)
	{
		delete metodo;
	}

	if ( mapaMetodos != NULL)
	{
		delete mapaMetodos;
	}
}

void Conexion::inicializar(struct mg_connection* mg_conexion)
{
	std::string contenidoTotal = std::string(mg_conexion->content);
	std::string nombreMetodo = std::string(mg_conexion->request_method);
	std::string uri = std::string(mg_conexion->uri);
	std::string query = (mg_conexion->query_string == NULL ) ? std::string("no_query") : std::string(mg_conexion->query_string);

	mapaMetodos = new std::map<std::string, METODOS>
		{
		{std::string("PUT"), PUT},
		{std::string("GET"), GET},
		{std::string("DELETE"), DELETE},
		{std::string("POST"), POST}
		};

	this->metodo = this->reconocerMetodo(nombreMetodo);
	this->uri = new Request::URI(uri);
	this->contenido = this->reconocerContenido(contenidoTotal, mg_conexion->content_len);
	this->query = query;
}

int Conexion::procesarRequest()
{
	//std::string entidad = this->uri->getEntidadAManejar();
	//ConexionServidor::BaseDeDatos::EntidadDB* entidad = this->uri->getEntidadAManejar();
	//ConexionServidor::Operaciones::IOperacion* operacion = this->uri->getOperacion();
	ConexionServidor::Operaciones::IOperable* operacion = ConexionServidor::Operaciones::CreadorDeOperaciones::getOperacion(uri);
	//this->metodo->ejecutar(operacion, this->contenido);
	//this->metodo->ejecutar(entidad, this->contenido);

	return 0;
}

Request::URI* Conexion::getUri()
{
	return this->uri;
}
Request::IMetodoREST* Conexion::getMetodo()
{
	return this->metodo;
}
std::string Conexion::getContenido()
{
	return this->contenido;
}
std::string Conexion::getQuery()
{
	return this->query;
}

Request::IMetodoREST* Conexion::reconocerMetodo(std::string nombre)
{
	if( mapaMetodos->find(nombre) == mapaMetodos->end() )
	{// si no encuentra el nombre en el mapa, entonces devuelve GET.
		return new Request::GET();
	}

	switch(mapaMetodos->at(nombre))
	{
		case DELETE: return new Request::DELETE();
		case GET: return new Request::GET();
		case POST: return new Request::POST();
		case PUT: return new Request::PUT();
		default: return new Request::GET();
	}
}

std::string Conexion::reconocerContenido(std::string contenidoTotal, int contenidoTamanio)
{
	return contenidoTotal.substr(0, contenidoTamanio);
}

std::string Conexion::impresion()
{
	std::string impresion;

	impresion = "Metodo: " + this->metodo->impresion() + "\nURI: " + this->uri->getURI() + "\nContenido: " + this->contenido + "\nQuery: " + this->query + "\n";

	return impresion;
}
