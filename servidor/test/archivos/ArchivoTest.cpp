/*
 * ArchivoTest.cpp
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#include "ArchivoTest.h"

using namespace Test;

const std::string ArchivoTest::archivoEjemplo1 =
"{\"nombre\":\"test1\",\"extension\":\"jpg\",\"etiqueta\":\"imagen\", \"fecha_ulti_modi\":\"26102015\","
"\"usuario_ulti_modi\":\"1234\", \"propietario\":\"1234\", \"baja_logica\":\"no\", \"direccion\":\"tmp/\"}";

const std::string ArchivoTest::archivoEjemplo2 =
"{\"nombre\":\"test2\",\"extension\":\"jpg\",\"etiqueta\":\"imagen\", \"fecha_ulti_modi\":\"26102015\","
"\"usuario_ulti_modi\":\"1234\", \"propietario\":\"1234\", \"baja_logica\":\"no\", \"direccion\":\"tmp/\"}";

const std::string ArchivoTest::archivoEjemplo3 =
"{\"nombre\":\"test3\",\"extension\":\"jpg\",\"etiqueta\":\"imagen\", \"fecha_ulti_modi\":\"26102015\","
"\"usuario_ulti_modi\":\"1234\", \"propietario\":\"1234\", \"baja_logica\":\"no\", \"direccion\":\"tmp/\"}";

char ArchivoTest::bytes[] = "estosSonUnosBytesDePrueba";

ArchivoTest::ArchivoTest() : archivo1(NULL)
{
	this->setUp();
}

ArchivoTest::~ArchivoTest()
{
	this->terminando();
}

void ArchivoTest::testSetYGetBytesCorrectamente()
{
	EXPECT_STREQ(bytes, this->archivo1->getTiraDeBytes());
}

void ArchivoTest::testGuardarArchivoCorrectamente()
{
	std::string path = this->archivo1->getPath();
	manager.eliminar( path ); // elimino archivo creado en testeos previos

	EXPECT_EQ( false, manager.existe( path ) );

	this->archivo1->guardar();

	EXPECT_EQ( true, manager.existe( path ) );

}
void ArchivoTest::testRecuperarArchivoCorrectamente()
{
	std::string path = this->archivo1->getPath();
	manager.eliminar( path ); // elimino archivo creado en testeos previos
	manager.escribir( path,  new Utiles::Bytes(bytes, tamanio) );

	this->archivo1->recuperar();

	EXPECT_STREQ( bytes, this->archivo1->getTiraDeBytes() );
}
void ArchivoTest::testModificarArchivoCorrectamente()
{

	this->archivo1->setBytes( new Utiles::Bytes("1234567890", 10) );

	this->archivo1->setDireccion( "direccion1/" );

	this->archivo1->modificar();

	std::string recuperado = manager.leer( this->archivo1->getPath() )->getStringDeBytes();

	EXPECT_STREQ( "1234567890", recuperado.c_str() );
	EXPECT_STREQ( "direccion1/", this->archivo1->getDireccion().c_str() );
}
void ArchivoTest::testEliminarArchivoCorrectamente()
{
	std::string path = this->archivo1->getPath();
	manager.escribir( path,  new Utiles::Bytes(bytes, tamanio) ); // lo creo para probar q elimine bien

	EXPECT_EQ( true, manager.existe( path ) );

	this->archivo1->eliminar();

	EXPECT_EQ( false, manager.existe( path ) );

	path = this->archivo1->getPath();
	manager.escribir( path,  new Utiles::Bytes(bytes, tamanio) ); // lo creo de nuevo

	EXPECT_EQ( true, manager.existe( path ) );

	this->archivo1->eliminarFisicamente();

	EXPECT_EQ( false, manager.existe( path ) );
}

void ArchivoTest::setUp()
{
	this->archivo1 = new ConexionServidor::BaseDeDatos::Archivo(archivoEjemplo1);
	this->archivo1->setBytes( new Utiles::Bytes(bytes, tamanio) );
}
void ArchivoTest::terminando()
{
	if ( this->archivo1 != NULL )
	{
		delete this->archivo1;
		this->archivo1 = NULL;
	}
}
