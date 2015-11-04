/*
 * ContenidoPorCarpetaTest.cpp
 *
 *  Created on: 4/11/2015
 *      Author: manuel
 */

#include "ContenidoPorCarpetaTest.h"

using namespace Test;

const std::string ContenidoPorCarpetaTest::contenidoEjemplo =
"{\"direccion\":\"carpetaTest/\", \"nombre\": \"test1\", \"archivos\":[\"archivo1\", \"archivo2\", \"archivo3\"], \"carpetas\": [ \"carpeta1\", \"carpeta2\", \"carpeta3\" ]}";

ContenidoPorCarpetaTest::ContenidoPorCarpetaTest() : contenido(NULL)
{
	this->setUp();
}

ContenidoPorCarpetaTest::~ContenidoPorCarpetaTest()
{
	this->terminando();
}

void ContenidoPorCarpetaTest::testCrearYRecuperarEnBDCorrectamente()
{
	this->contenido->guardar();

	std::string contenidoRecuperado = this->contenido->recuperar();

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoLogicoRecuperado;
	contenidoLogicoRecuperado.setContenido(contenidoRecuperado);

	EXPECT_STREQ(this->contenido->getContenido().c_str(), contenidoLogicoRecuperado.getContenido().c_str());
}

void ContenidoPorCarpetaTest::testModificarEnBDCorrectamente()
{
	this->contenido->guardar();

	EXPECT_STREQ("carpetaTest/test1", this->contenido->getPath().c_str());
	EXPECT_STREQ("archivo2", this->contenido->getArchivos()[1].c_str());
	EXPECT_STREQ("carpeta3", this->contenido->getCarpetas()[2].c_str());

	//this->contenido->setPath("carpetaTest/test2/");
	this->contenido->setDireccion("carpetaTest/");
	this->contenido->setNombre("test2");
	this->contenido->agregarArchivo("archivo20");
	this->contenido->eliminarArchivo("archivo2");
	this->contenido->agregarCarpeta("carpeta40");
	this->contenido->eliminarCarpeta("carpeta3");

	this->contenido->modificar();

	std::string contenidoNuevo = this->contenido->recuperar();

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoLogicoNuevo;
	contenidoLogicoNuevo.setContenido(contenidoNuevo);

	EXPECT_STREQ("carpetaTest/test2", contenidoLogicoNuevo.getPath().c_str());
	EXPECT_STREQ("archivo3", contenidoLogicoNuevo.getArchivos()[1].c_str() );
	EXPECT_STREQ("archivo20", contenidoLogicoNuevo.getArchivos()[2].c_str() );
	EXPECT_STREQ("carpeta40", contenidoLogicoNuevo.getCarpetas()[2].c_str() );
}

void ContenidoPorCarpetaTest::testEliminarEnBDCorrectamente()
{

}
void ContenidoPorCarpetaTest::testSetearPathCorrectamente()
{
	this->contenido->setPath("este/es/un/path/");

	EXPECT_STREQ("este/es/un/", this->contenido->getDireccion().c_str());
	EXPECT_STREQ("path", this->contenido->getNombre().c_str());

	this->contenido->setPath("este/es/otro/path/SinBarra");

	EXPECT_STREQ("este/es/otro/path/", this->contenido->getDireccion().c_str());
	EXPECT_STREQ("SinBarra", this->contenido->getNombre().c_str());
}
void ContenidoPorCarpetaTest::testDevolvePathCorrecto()
{
	EXPECT_STREQ("carpetaTest/test1", this->contenido->getPath().c_str());
}

void ContenidoPorCarpetaTest::setUp()
{
	this->contenido = new ConexionServidor::BaseDeDatos::ContenidoPorCarpeta(contenidoEjemplo);
}

void ContenidoPorCarpetaTest::terminando()
{
	if ( this->contenido != NULL )
	{
		delete this->contenido;
		this->contenido = NULL;
	}
}
