/*
 * CarpetaLogicaTest.h
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#ifndef CARPETALOGICATEST_H_
#define CARPETALOGICATEST_H_

// gtest
#include <gtest/gtest.h>

// User
#include "../../../src/bd/entidades/CarpetaLogica.h"

namespace Test
{

class CarpetaLogicaTest : public testing::Test
{
public:
	CarpetaLogicaTest();
	virtual ~CarpetaLogicaTest();

	static const std::string carpetaEjemplo;

	void testCrearYRecuperarEnBDCorrectamente();
	void testModificarEnBDCorrectamente();
	void testEliminarEnBDCorrectamente();
	void testModificarAtributoCorrectamente();
	void testDevolvePathCorrecto();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::CarpetaLogica* carpeta;
};

TEST_F(CarpetaLogicaTest, crearYRecuperarEnBD)
{
	CarpetaLogicaTest test;
	test.testCrearYRecuperarEnBDCorrectamente();
}
TEST_F(CarpetaLogicaTest, modificarEnBD)
{
	CarpetaLogicaTest test;
	test.testModificarEnBDCorrectamente();
}
TEST_F(CarpetaLogicaTest, eliminarEnBD)
{
	CarpetaLogicaTest test;
	test.testEliminarEnBDCorrectamente();
}
TEST_F(CarpetaLogicaTest, modificarAtributo)
{
	CarpetaLogicaTest test;
	test.testModificarAtributoCorrectamente();
}
TEST_F(CarpetaLogicaTest, devolverPath)
{
	CarpetaLogicaTest test;
	test.testDevolvePathCorrecto();
}
};

#endif /* CARPETALOGICATEST_H_ */
