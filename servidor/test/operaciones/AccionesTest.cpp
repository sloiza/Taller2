/*
 * AccionesTest.cpp
 *
 *  Created on: 21/11/2015
 *      Author: manuel
 */

#include "AccionesTest.h"

using namespace Test;

const std::string AccionesTest::archivoEjemplo =
"{\"nombre\":\"test3\",\"extension\":\"txt\",\"etiqueta\":\"imagen\", \"fecha_ulti_modi\":\"26102015\","
"\"usuario_ulti_modi\":\"1234\", \"propietario\":\"1234\", \"baja_logica\":\"no\", \"direccion\":\"tmp/\"}";

char AccionesTest::bytes[] = "estosSonUnosBytesDePrueba";

AccionesTest::AccionesTest() : archivoFisico(NULL),  archivoLogico(NULL)
{
	this->setUp();
}

AccionesTest::~AccionesTest()
{
	this->terminando();
}

void AccionesTest::testAltaLogicaArchivoCorrectamente()
{
	bool res = this->acciones.darDeAltaArchivoLogico( archivoLogico );

	EXPECT_EQ( true, res );

	res = this->acciones.darDeAltaArchivoLogico( archivoLogico );

	EXPECT_EQ( false, res );
}
void AccionesTest::testAltaFisicaArchivoCorrectamente()
{
	bool res = this->acciones.darDeAltaArchivoFisico( archivoFisico );

	EXPECT_EQ( true, res );

	res = this->acciones.darDeAltaArchivoFisico( archivoFisico );

	EXPECT_EQ( false, res );
}

void AccionesTest::setUp()
{
	this->archivoFisico = new ConexionServidor::BaseDeDatos::Archivo(archivoEjemplo);
	this->archivoFisico->setBytes( new Utiles::Bytes(bytes, tamanio) );

	this->archivoLogico = new ConexionServidor::BaseDeDatos::ArchivoLogico(archivoEjemplo);
}
void AccionesTest::terminando()
{
	if ( this->archivoFisico != NULL )
	{
		delete this->archivoFisico;
		this->archivoFisico = NULL;
	}
	if ( this->archivoLogico != NULL )
	{
		delete this->archivoLogico;
		this->archivoLogico = NULL;
	}
}
