/*
 * ManagerBDTest.h
 *
 *  Created on: 12/10/2015
 *      Author: manuel
 */

#ifndef MANAGERBDTEST_H_
#define MANAGERBDTEST_H_

// gtest
#include <gtest/gtest.h>

// Base de datos
#include "../../src/bd/ClaveRocksDB.h"
#include "../../src/bd/ManagerBD.h"

namespace Test
{

class ManagerBDTest : public testing::Test{
public:
	ManagerBDTest();
	virtual ~ManagerBDTest();

	void testInicializadaYCerradaCorrectamente();
	void testInsertarYRecuperarRegistro();
	void testEliminarRegistro();

	void TestBody() {};
protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	ConexionServidor::BaseDeDatos::ManagerBD* manager;
	ConexionServidor::BaseDeDatos::ClaveRocksDB clave = {"user", "1"};

};

TEST_F(ManagerBDTest, InicializadaYCerradaCorrectamente)
{
	ManagerBDTest test;
	test.testInicializadaYCerradaCorrectamente();
}

TEST_F(ManagerBDTest, insertarYRecuperarRegistro)
{
	ManagerBDTest test;
	test.testInsertarYRecuperarRegistro();
}

TEST_F(ManagerBDTest, EliminarRegistro)
{
	ManagerBDTest test;
	test.testEliminarRegistro();
}

};
#endif /* MANAGERBDTEST_H_ */
