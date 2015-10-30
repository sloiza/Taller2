/*
 * CreadorDeOperacionesTest.cpp
 *
 *  Created on: 29/10/2015
 *      Author: manuel
 */

#include "CreadorDeOperacionesTest.h"

using namespace Test;

CreadorDeOperacionesTest::CreadorDeOperacionesTest() : creador(NULL)
{
	this->setUp();
}

CreadorDeOperacionesTest::~CreadorDeOperacionesTest()
{
	this->terminando();
}

void CreadorDeOperacionesTest::testDividirUriVacia()
{
	std::string uriVacia = "";
	this->creador->dividirRecursos(uriVacia);

	EXPECT_EQ(0, this->creador->getCampos().size());
}
void CreadorDeOperacionesTest::testDividirUriSinQuery()
{
	std::string uriSinQuery = "usuario/miBaul";

	this->creador->dividirRecursos(uriSinQuery);

	EXPECT_STREQ("usuario", this->creador->getCampos()[0].c_str());
	EXPECT_STREQ("miBaul", this->creador->getCampos()[1].c_str());

	EXPECT_EQ(2, this->creador->getCampos().size());

}
void CreadorDeOperacionesTest::testDividirUriConQuery()
{
	std::string uriConQuery = "usuario/miBaul?descargar=unArchivo.txt";

	this->creador->dividirRecursos(uriConQuery);

	EXPECT_STREQ("usuario", this->creador->getCampos()[0].c_str());
	EXPECT_STREQ("miBaul", this->creador->getCampos()[1].c_str());
	EXPECT_STREQ("descargar", this->creador->getCampos()[2].c_str());

	EXPECT_EQ(3, this->creador->getCampos().size());

}
void CreadorDeOperacionesTest::testReconocerOperacionesCorrectamente()
{

}
void CreadorDeOperacionesTest::testDevolverErrorCuandoNoSeEncuentraRecurso()
{

}

void CreadorDeOperacionesTest::setUp()
{
	this->creador = new ConexionServidor::Operaciones::CreadorDeOperaciones();
}
void CreadorDeOperacionesTest::terminando()
{
	if ( this->creador != NULL )
	{
		delete this->creador;
		this->creador = NULL;
	}
}
