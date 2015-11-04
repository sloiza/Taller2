/*
 * CarpetaLogicaTest.cpp
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#include "CarpetaLogicaTest.h"

using namespace Test;

const std::string CarpetaLogicaTest::carpetaEjemplo =
"{\"nombre\":\"carpetaTest\", \"etiqueta\":\"vacaciones\", \"fecha_ulti_modi\":\"03112015\","
"\"usuario_ulti_modi\":\"1234\", \"propietario\":\"1234\", \"baja_logica\":\"no\", \"direccion\":\"tmp/\"}";

CarpetaLogicaTest::CarpetaLogicaTest() : carpeta(NULL)
{
	this->setUp();
}

CarpetaLogicaTest::~CarpetaLogicaTest()
{
	this->terminando();
}

void CarpetaLogicaTest::testCrearYRecuperarEnBDCorrectamente()
{
	this->carpeta->guardar();

	std::string contenidoRecuperado = this->carpeta->recuperar();

	ConexionServidor::BaseDeDatos::CarpetaLogica carpetaRecuperada;
	carpetaRecuperada.setContenido(contenidoRecuperado);

	EXPECT_STREQ(this->carpeta->getContenido().c_str(), carpetaRecuperada.getContenido().c_str());
}

void CarpetaLogicaTest::testModificarEnBDCorrectamente()
{
	this->carpeta->guardar();

	EXPECT_STREQ("carpetaTest", this->carpeta->getNombre().c_str());
	EXPECT_STREQ("vacaciones", this->carpeta->getEtiqueta().c_str());

	this->carpeta->setNombre("carpetaTest_bis");
	this->carpeta->setEtiqueta("vacaciones 2014");

	this->carpeta->modificar();

	std::string contenidoNuevo = this->carpeta->recuperar();

	ConexionServidor::BaseDeDatos::CarpetaLogica carpetaNueva;
	carpetaNueva.setContenido(contenidoNuevo);

	EXPECT_STREQ("carpetaTest_bis", carpetaNueva.getNombre().c_str());
	EXPECT_STREQ("vacaciones 2014", carpetaNueva.getEtiqueta().c_str());
}

void CarpetaLogicaTest::testEliminarEnBDCorrectamente()
{

}

void CarpetaLogicaTest::testModificarAtributoCorrectamente()
{
	std::string nombre = this->carpeta->getNombre();

	EXPECT_STREQ("carpetaTest", nombre.c_str());

	this->carpeta->setNombre("carpetaTest_bis");

	std::string nombreNuevo = this->carpeta->getNombre();

	EXPECT_STREQ("carpetaTest_bis", nombreNuevo.c_str());
}

void CarpetaLogicaTest::testDevolvePathCorrecto()
{
	EXPECT_STREQ("tmp/carpetaTest", this->carpeta->getPath().c_str());
}

void CarpetaLogicaTest::setUp()
{
	this->carpeta = new ConexionServidor::BaseDeDatos::CarpetaLogica(carpetaEjemplo);
}

void CarpetaLogicaTest::terminando()
{
	if ( this->carpeta != NULL )
	{
		delete this->carpeta;
		this->carpeta = NULL;
	}
}
