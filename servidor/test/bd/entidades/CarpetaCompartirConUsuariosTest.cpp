/*
 * CarpetaCompartirConUsuariosTest.cpp
 *
 *  Created on: 14/11/2015
 *      Author: manuel
 */

#include "CarpetaCompartirConUsuariosTest.h"

using namespace Test;

const std::string CarpetaCompartirConUsuariosTest::compartirEjemplo =
"{ \"nombre\":\"carpetaCompartida\", \"direccion\": \"tmp/\", \"usuarios\": [ \"manu2@gmail.com\", \"manu4@gmail.com\" ] }";

CarpetaCompartirConUsuariosTest::CarpetaCompartirConUsuariosTest() : carpetaCompartir(NULL)
{
	this->setUp();
}

CarpetaCompartirConUsuariosTest::~CarpetaCompartirConUsuariosTest()
{
	this->terminando();
}

void CarpetaCompartirConUsuariosTest::testRecuperarCarpetaCorrectamente()
{
	std::string nombre = carpetaCompartir->getNombreCarpeta();

	EXPECT_STREQ("carpetaCompartida", nombre.c_str());
}
void CarpetaCompartirConUsuariosTest::testRecuperarUsuariosCorrectamente()
{
	std::vector<std::string> usuarios = carpetaCompartir->getUsuariosACompartirles();

	EXPECT_STREQ("manu2@gmail.com", usuarios[0].c_str());
	EXPECT_STREQ("manu4@gmail.com", usuarios[1].c_str());
}

void CarpetaCompartirConUsuariosTest::setUp()
{
	this->carpetaCompartir = new ConexionServidor::BaseDeDatos::CarpetaCompartirConUsuarios(compartirEjemplo);
}

void CarpetaCompartirConUsuariosTest::terminando()
{
	if ( this->carpetaCompartir != NULL )
	{
		delete this->carpetaCompartir;
		this->carpetaCompartir = NULL;
	}
}
