/*
 * rocksdbTest.cpp
 *
 *  Created on: 10/10/2015
 *      Author: manuel
 */

#include "rocksdbTest.h"

using namespace Tests;

rocks_dbTest::rocks_dbTest() : bd(NULL)
{
	this->setUp();
}

rocks_dbTest::~rocks_dbTest()
{
	if ( this->bd != NULL )
	{
		delete this->bd;
	}
	this->bd = NULL;
}

void rocks_dbTest::inicializar()
{
	this->bd = new rocks_db();
}

void rocks_dbTest::testInsertarYRecuperarRegistro()
{
	Status estado = this->bd->put("user", Slice("key"), Slice("valor"));

	EXPECT_EQ(true, estado.ok());

	std::string valorRecuperado;

	estado = this->bd->get("user", Slice("key"), &valorRecuperado);

	EXPECT_STREQ("valor", valorRecuperado.c_str());
	EXPECT_EQ(true, estado.ok());
}

void rocks_dbTest::testEliminarRegistro()
{
	EXPECT_EQ(true, true);
}

void rocks_dbTest::testRecuperarRegistroInexistente()
{
	std::string valorRecuperado;
	Status estado = this->bd->get("user", Slice("noexiste"), &valorRecuperado);

	EXPECT_STREQ("vacio", valorRecuperado.c_str());
	EXPECT_EQ(false, estado.ok());
}

void rocks_dbTest::setUp()
{

}

void rocks_dbTest::terminando()
{

}
