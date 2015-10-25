/*
 * JsonInfoTest.cpp
 *
 *  Created on: 12/10/2015
 *      Author: manuel
 */

#include "JsonInfoTest.h"

using namespace Test;

const std::string JsonInfoTest::jsonEjemplo =
"{\"id\": 1234,\"nombre\":\"Arturo\",\"apellido\":\"Perez\",\"mails\":[\"arthur@gmail.com\", \"arturito2000@hotmail.com\"]}";

JsonInfoTest::JsonInfoTest() : info(NULL)
{
	this->setUp();
}

JsonInfoTest::~JsonInfoTest()
{
	this->finishing();
}

void JsonInfoTest::testContenidoNoValido()
{
	ConexionServidor::BaseDeDatos::JsonInfo* info = new  ConexionServidor::BaseDeDatos::JsonInfo("contenidoNoValido");

	EXPECT_EQ(false, info->estadoOk());

	delete info;
}

void JsonInfoTest::testCrearCorrectamente()
{
	ConexionServidor::BaseDeDatos::JsonInfo* info = new  ConexionServidor::BaseDeDatos::JsonInfo(jsonEjemplo);

	EXPECT_EQ(true, info->estadoOk());

	delete info;
}

void JsonInfoTest::testGetCampoBien()
{
	std::string nombre = this->info->getAtributo("nombre", "default");
	std::string apellido = this->info->getAtributo("apellido", "default");

	EXPECT_STREQ("Arturo", nombre.c_str());
	EXPECT_STREQ("Perez", apellido.c_str());
	EXPECT_EQ(true, this->info->estadoOk());
}

void JsonInfoTest::testSettearYRecuperarCampoCorrectamente()
{
	this->info->setAtributo("saludo", "Hola!");

	std::string saludo = this->info->getAtributo("saludo", "default");

	EXPECT_STREQ("Hola!", saludo.c_str());
	EXPECT_EQ(true, this->info->estadoOk());
}

void JsonInfoTest::testGetValorPorDefaultCorrecto()
{
	std::string porDefault = this->info->getAtributo("unCampo", "default");

	EXPECT_STREQ("default", porDefault.c_str());
	EXPECT_EQ(true, this->info->estadoOk());
}

void JsonInfoTest::testCambiarContenidoCorrectamente()
{
	std::string nuevoContenido("{ \"unCampo\": \"unValor\" }");
	//nuevoContenido = "{ \"unCampo\": \unValor\" }"

	this->info->setContenido(nuevoContenido);

	std::string unValor = this->info->getAtributo("unCampo", "default");
	std::string nombre = this->info->getAtributo("nombre", "default");

	EXPECT_STREQ("unValor", unValor.c_str());
	EXPECT_STREQ("default", nombre.c_str());
	EXPECT_EQ(true, this->info->estadoOk());
}

void JsonInfoTest::setUp()
{
	this->info = new ConexionServidor::BaseDeDatos::JsonInfo(jsonEjemplo);
}

void JsonInfoTest::finishing()
{
	if (info != NULL)
	{
		delete info;
		info = NULL;
	}
}
