/*
 * ArchivoCompartirConUsuarioTest.cpp
 *
 *  Created on: 28/11/2015
 *      Author: manuel
 */

#include "ArchivoCompartirConUsuarioTest.h"

using namespace Test;

const std::string ArchivoCompartirConUsuarioTest::archivoEjemplo =
"{\"nombre\":\"foto_09082015\",\"extension\":\"jpg\",\"direccion\":\"tmp/\", \"usuarios\":[ \"manu@gmail.com\" , \"rober@gmail.com\"] }";

ArchivoCompartirConUsuarioTest::ArchivoCompartirConUsuarioTest()
{
	this->setUp();
}

ArchivoCompartirConUsuarioTest::~ArchivoCompartirConUsuarioTest()
{
	this->terminando();
}

void ArchivoCompartirConUsuarioTest::testSetYGetAtributosCorrectamente()
{
	EXPECT_STREQ( "foto_09082015", archivoCompartir->getNombreArchivo().c_str() );
	EXPECT_STREQ( "tmp/", archivoCompartir->getDireccionArchivo().c_str() );
	EXPECT_STREQ( "jpg", archivoCompartir->getExtensionArchivo().c_str() );
	EXPECT_STREQ( "tmp/foto_09082015.jpg", archivoCompartir->getPathArchivo().c_str() );
	EXPECT_STREQ( "rober@gmail.com", archivoCompartir->getUsuariosACompartirles()[1].c_str() );
}
void ArchivoCompartirConUsuarioTest::testMetodosEntidad()
{
	ConexionServidor::BaseDeDatos::ArchivoCompartirConUsuarios* archivoCompartir2 = new ConexionServidor::BaseDeDatos::ArchivoCompartirConUsuarios();

	archivoCompartir2->setContenido( this->archivoCompartir->getValor() );
}

void ArchivoCompartirConUsuarioTest::setUp()
{
	this->archivoCompartir = new ConexionServidor::BaseDeDatos::ArchivoCompartirConUsuarios(archivoEjemplo);
}

void ArchivoCompartirConUsuarioTest::terminando()
{
	if ( this->archivoCompartir != NULL )
	{
		delete this->archivoCompartir;
		this->archivoCompartir = NULL;
	}
}
