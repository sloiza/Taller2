/*
 * CarpetaTest.cpp
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#include "CarpetaTest.h"

using namespace Test;

const std::string CarpetaTest::carpetaEjemplo =
"{\"nombre\":\"carpetaTest\", \"etiqueta\": [ \"vacaciones\" ], \"fecha_ulti_modi\":\"03112015\","
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
	EXPECT_EQ( true, this->carpeta->existeFisicamente() );

	this->carpeta->eliminar();

	EXPECT_EQ( false, this->manager.existe( this->carpeta->getPath() ) );
}
void CarpetaTest::testModificarCarpetaCorrectamente()
{
	this->carpeta->setNombre( "carpetusa" );
	this->carpeta->agregarEtiqueta( "trabajo" );
	this->carpeta->setUltimaFechaModif( "20151127" );
	this->carpeta->setUltimoUsuarioModif( "manu@gmail.com" );
	this->carpeta->setPropietario( "roberto" );
	this->carpeta->setBajaLogica("si");
	this->carpeta->setDireccion( "misCarpetas/" );

	this->carpeta->modificar();

	EXPECT_STREQ( "carpetusa", this->carpeta->getNombre().c_str() );
	EXPECT_STREQ( "trabajo", this->carpeta->getEtiquetas()[1].c_str() );
	EXPECT_STREQ( "20151127", this->carpeta->getUltimaFechaModif().c_str() );
	EXPECT_STREQ( "manu@gmail.com", this->carpeta->getUltimoUsuarioModif().c_str() );
	EXPECT_STREQ( "roberto", this->carpeta->getPropietario().c_str() );
	EXPECT_STREQ( "si", this->carpeta->getBajaLogica().c_str() );
	EXPECT_STREQ( "misCarpetas/", this->carpeta->getDireccion().c_str() );
}
void CarpetaTest::testCrearCarpetaConContenido()
{
	ConexionServidor::BaseDeDatos::Carpeta* carpeta1 = new ConexionServidor::BaseDeDatos::Carpeta();
	carpeta1->setContenido( this->carpeta->getValor() );

	EXPECT_STREQ( "tmp/carpetaTest" ,carpeta1->getPath().c_str() );

	carpeta1->setNombre( "carpetaVacia" );

	EXPECT_EQ( true ,carpeta1->estaVacia() );
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
