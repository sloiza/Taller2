/*
 * CarpetaTest.h
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#ifndef CARPETATEST_H_
#define CARPETATEST_H_

// gtest
#include <gtest/gtest.h>

// Archivo
#include "../../src/archivos/Carpeta.h"
#include "../../src/archivos/ManagerArchivos.h"

namespace Test
{

class CarpetaTest : public testing::Test
{
public:
	CarpetaTest();
	virtual ~CarpetaTest();

	static const std::string carpetaEjemplo;

	void testCrearCarpetaCorrectamente();
	void testEliminarCarpetaCorrectamente();
	void testModificarCarpetaCorrectamente();
	void testCrearCarpetaConContenido();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::Carpeta* carpeta;
	ConexionServidor::BaseDeDatos::ManagerArchivos manager;
};

TEST_F(CarpetaTest, crearCarpeta)
{
	CarpetaTest test;
	test.testCrearCarpetaCorrectamente();
}
TEST_F(CarpetaTest, eliminarCarpeta)
{
	CarpetaTest test;
	test.testEliminarCarpetaCorrectamente();
}
TEST_F(CarpetaTest, modificarCarpeta)
{
	CarpetaTest test;
	test.testModificarCarpetaCorrectamente();
}
TEST_F(CarpetaTest, crearOtraCarpeta)
{
	CarpetaTest test;
	test.testCrearCarpetaConContenido();
}
};

#endif /* CARPETATEST_H_ */
