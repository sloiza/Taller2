/*
 * CarpetaTest.cpp
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#include "CarpetaTest.h"

using namespace Test;

const std::string CarpetaTest::carpetaEjemplo =
"{\"nombre\":\"carpetaTest\", \"etiqueta\":\"vacaciones\", \"fecha_ulti_modi\":\"03112015\","
"\"usuario_ulti_modi\":\"1234\", \"propietario\":\"1234\", \"baja_logica\":\"no\", \"direccion\":\"tmp/\"}";

CarpetaTest::CarpetaTest() : carpeta(NULL)
{
	this->setUp();
}

CarpetaTest::~CarpetaTest()
{
	this->terminando();
}

void CarpetaTest::testCrearCarpetaCorrectamente()
{
	EXPECT_EQ( false, this->manager.existe( this->carpeta->getPath() ) );

	this->carpeta->guardar();

	EXPECT_EQ( true, this->manager.existe( this->carpeta->getPath() ) );

	this->manager.eliminarCarpetaVacia( this->carpeta->getPath() ); // elimino para q qede como estaba
}
void CarpetaTest::testEliminarCarpetaCorrectamente()
{
	this->manager.crearCarpeta( this->carpeta->getPath() ); // la creo para dsp probar la eliminacion

	EXPECT_EQ( true, this->manager.existe( this->carpeta->getPath() ) );

	this->carpeta->eliminar();

	EXPECT_EQ( false, this->manager.existe( this->carpeta->getPath() ) );
}

void CarpetaTest::setUp()
{
	this->carpeta = new ConexionServidor::BaseDeDatos::Carpeta(carpetaEjemplo);
}
void CarpetaTest::terminando()
{
	if ( this->carpeta != NULL )
	{
		delete this->carpeta;
		this->carpeta = NULL;
	}
}
