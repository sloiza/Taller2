/*
 * OperacionBusquedaTest.cpp
 *
 *  Created on: 18/11/2015
 *      Author: manuel
 */

#include "OperacionBusquedaTest.h"

using namespace Test;

const std::string OperacionBusquedaTest::archivoEjemplo1 =
		"{\"nombre\":\"nombre1\",\"extension\":\"extension1\",\"etiqueta\":\"etiqueta1\", \"fecha_ulti_modi\":\"26102015\","
		"\"direccion\":\"direccion1/\",\"usuario_ulti_modi\":\"1234\", \"propietario\":\"propietario1\", \"baja_logica\":\"no\"}";

const std::string OperacionBusquedaTest::archivoEjemplo2 =
		"{\"nombre\":\"nombre2\",\"extension\":\"extension2\",\"etiqueta\":\"etiqueta2\", \"fecha_ulti_modi\":\"26102015\","
		"\"direccion\":\"direccion2/\",\"usuario_ulti_modi\":\"1234\", \"propietario\":\"propietario2\", \"baja_logica\":\"no\"}";

const std::string OperacionBusquedaTest::archivoEjemplo3 =
		"{\"nombre\":\"nombre3\",\"extension\":\"extension3\",\"etiqueta\":\"etiqueta3\", \"fecha_ulti_modi\":\"26102015\","
		"\"direccion\":\"direccion3/\",\"usuario_ulti_modi\":\"1234\", \"propietario\":\"propietario3\", \"baja_logica\":\"no\"}";

const std::string OperacionBusquedaTest::archivoEjemplo4 =
		"{\"nombre\":\"nombre4\",\"extension\":\"extension4\",\"etiqueta\":\"etiqueta4\", \"fecha_ulti_modi\":\"26102015\","
		"\"direccion\":\"direccion/del/archivo4/\",\"usuario_ulti_modi\":\"1234\", \"propietario\":\"propietario4\", \"baja_logica\":\"no\"}";

const std::string OperacionBusquedaTest::archivoEjemplo5 =
		"{\"nombre\":\"nombre5\",\"extension\":\"extension5\",\"etiqueta\":\"etiqueta5\", \"fecha_ulti_modi\":\"26102015\","
		"\"direccion\":\"direccion5/\",\"usuario_ulti_modi\":\"1234\", \"propietario\":\"propietario5\", \"baja_logica\":\"no\"}";

const std::string OperacionBusquedaTest::archivoEjemplo6 =
		"{\"nombre\":\"nombre6\",\"extension\":\"extension6\",\"etiqueta\":\"etiqueta6\", \"fecha_ulti_modi\":\"26102015\","
		"\"direccion\":\"direccion6/\",\"usuario_ulti_modi\":\"1234\", \"propietario\":\"propietario6\", \"baja_logica\":\"no\"}";

OperacionBusquedaTest::OperacionBusquedaTest()
{
	this->setUp();
}

OperacionBusquedaTest::~OperacionBusquedaTest()
{
	this->terminando();
}

void OperacionBusquedaTest::testBuscarPorNombreCorrectamente()
{
	std::vector<std::string> resultados = buscador->buscarArchivosPorNombre( listaArchivos, "nombre2" );

	EXPECT_STREQ( "direccion2/nombre2.extension2", resultados[0].c_str() );

	resultados = buscador->buscarArchivosPorNombre( listaArchivos, "nombre4" );

	EXPECT_STREQ( "direccion/del/archivo4/nombre4.extension4", resultados[0].c_str() );
}
void OperacionBusquedaTest::testBuscarPorEtiquetaCorrectamente()
{

}
void OperacionBusquedaTest::testBuscarPorExtensionCorrectamente()
{

}
void OperacionBusquedaTest::testBuscarPorPropietarioCorrectamente()
{

}

void OperacionBusquedaTest::setUp()
{
	this->buscador = new ConexionServidor::Operaciones::OperacionBusqueda();

	ConexionServidor::BaseDeDatos::ArchivoLogico* archivo1 = new ConexionServidor::BaseDeDatos::ArchivoLogico(archivoEjemplo1);
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivo2 = new ConexionServidor::BaseDeDatos::ArchivoLogico(archivoEjemplo2);
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivo3 = new ConexionServidor::BaseDeDatos::ArchivoLogico(archivoEjemplo3);
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivo4 = new ConexionServidor::BaseDeDatos::ArchivoLogico(archivoEjemplo4);
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivo5 = new ConexionServidor::BaseDeDatos::ArchivoLogico(archivoEjemplo5);
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivo6 = new ConexionServidor::BaseDeDatos::ArchivoLogico(archivoEjemplo6);

	listaArchivos.push_back(archivo1);
	listaArchivos.push_back(archivo2);
	listaArchivos.push_back(archivo3);
	listaArchivos.push_back(archivo4);
	listaArchivos.push_back(archivo5);
	listaArchivos.push_back(archivo6);
}
void OperacionBusquedaTest::terminando()
{
	if ( this->buscador != NULL )
	{
		delete this->buscador;
		this->buscador = NULL;
	}

	for ( std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*>::iterator it = listaArchivos.begin() ; it != listaArchivos.end() ; it++)
	{
		delete *it;
	}
	listaArchivos.clear();
}

