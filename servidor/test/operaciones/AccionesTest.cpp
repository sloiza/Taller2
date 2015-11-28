/*
 * AccionesTest.cpp
 *
 *  Created on: 21/11/2015
 *      Author: manuel
 */

#include "AccionesTest.h"

using namespace Test;

const std::string AccionesTest::archivoEjemplo =
"{\"nombre\":\"accionesTesteo\",\"extension\":\"txt\",\"etiqueta\":\"imagen\", \"fecha_ulti_modi\":\"26102015\","
"\"usuario_ulti_modi\":\"1234\", \"propietario\":\"1234\", \"baja_logica\":\"no\", \"direccion\":\"tmp/\"}";

const std::string AccionesTest::queryEjemplo =
"nombre=resumen_sistemas_distribuido&extension=pdf&etiqueta=file+tp+facultad&fecha_ulti_modi=222902015_102908&usuario_ulti_modi=Mati+Carreras+&propietario=Mati+Carreras+&baja_logica=no&direccion=tmp/Mncarreras@hotmail.com/";


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
void AccionesTest::testDarDeBajaArchivoLogicoCorrectamente()
{// precondicion: archivo creado por 'testAltaLogicaArchivoCorrectamente'.

	bool res = this->acciones.darDeBajaArchivoLogico(archivoLogico);

	EXPECT_EQ( true, res );

	res = this->acciones.darDeBajaArchivoLogico(archivoLogico);

	EXPECT_EQ( false, res );
}
void AccionesTest::testAgregarArchivoLogicoASuCarpetaLogicaCorrectamente()
{
	bool res = this->acciones.agregarArchivoLogicoASuCarpetaLogica( archivoLogico );

	EXPECT_EQ( true, res );

	res = this->acciones.agregarArchivoLogicoASuCarpetaLogica( archivoLogico );

	EXPECT_EQ( false, res );
}
void AccionesTest::testSacarArchivoLogicoDeSuCarpetaLogicaCorrectamente()
{// precondicion: archivo agregado por 'testAgregarArchivoLogicoASuCarpetaLogicaCorrectamente'.

	bool res = this->acciones.sacarArchivoLogicoDeSuCarpetaLogica( archivoLogico );

	EXPECT_EQ( true, res );

	res = this->acciones.sacarArchivoLogicoDeSuCarpetaLogica( archivoLogico );

	EXPECT_EQ( false, res );
}
void AccionesTest::testAgregarArchivoLogicoAPapeleraCorrectamente()
{

}
void AccionesTest::testParsearArchivoDeQueryCorrectamente()
{
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoParseado = this->acciones.parsearArchivoDeQuery( queryEjemplo );

	EXPECT_STREQ( "resumen_sistemas_distribuido" , archivoParseado->getNombre().c_str() );
	EXPECT_STREQ( "pdf" , archivoParseado->getExtension().c_str() );
	EXPECT_STREQ( base64_decode("file").c_str() , archivoParseado->getEtiquetas()[0].c_str() );
	EXPECT_STREQ( base64_decode("tp").c_str() , archivoParseado->getEtiquetas()[1].c_str() );
	EXPECT_STREQ( base64_decode("facultad").c_str() , archivoParseado->getEtiquetas()[2].c_str() );
	EXPECT_STREQ( base64_decode("222902015_102908").c_str() , archivoParseado->getUltimaFechaModif().c_str() );
	EXPECT_STREQ( "Mati Carreras " , archivoParseado->getUltimoUsuarioModif().c_str() );
	EXPECT_STREQ( "Mati Carreras " , archivoParseado->getPropietario().c_str() );
	EXPECT_STREQ( "no" , archivoParseado->getBajaLogica().c_str() );
	EXPECT_STREQ( "tmp/Mncarreras@hotmail.com/" , archivoParseado->getDireccion().c_str() );
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
