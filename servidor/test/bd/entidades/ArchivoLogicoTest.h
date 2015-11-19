/*
 * ArchivoLogicoTest.h
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#ifndef ARCHIVOLOGICOTEST_H_
#define ARCHIVOLOGICOTEST_H_

// gtest
#include <gtest/gtest.h>

// User
#include "../../../src/bd/entidades/ArchivoLogico.h"

namespace Test
{

class ArchivoLogicoTest : public testing::Test
{

public:
	ArchivoLogicoTest();
	virtual ~ArchivoLogicoTest();

	static const std::string archivoEjemplo;

	void testCrearYRecuperarEnBDCorrectamente();
	void testModificarEnBDCorrectamente();
	void testEliminarEnBDCorrectamente();
	void testModificarAtributoCorrectamente();

	void testSetearPathCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::ArchivoLogico* archivo;
};

TEST_F(ArchivoLogicoTest, crearYRecuperarEnBD)
{
	ArchivoLogicoTest test;
	test.testCrearYRecuperarEnBDCorrectamente();
}

TEST_F(ArchivoLogicoTest, modificarEnBD)
{
	ArchivoLogicoTest test;
	test.testModificarEnBDCorrectamente();
}

TEST_F(ArchivoLogicoTest, eliminarEnBD)
{
	ArchivoLogicoTest test;
	test.testEliminarEnBDCorrectamente();
}

TEST_F(ArchivoLogicoTest, modificarAtributo)
{
	ArchivoLogicoTest test;
	test.testModificarAtributoCorrectamente();
}
TEST_F(ArchivoLogicoTest, setearPath)
{
	ArchivoLogicoTest test;
	test.testSetearPathCorrectamente();
}
}

#endif /* ARCHIVOLOGICOTEST_H_ */
