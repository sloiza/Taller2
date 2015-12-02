/*
 * ArchivoCompartirConUsuarioTest.h
 *
 *  Created on: 28/11/2015
 *      Author: manuel
 */

#ifndef ARCHIVOCOMPARTIRCONUSUARIOTEST_H_
#define ARCHIVOCOMPARTIRCONUSUARIOTEST_H_

// gtest
#include <gtest/gtest.h>

// User
#include "../../../src/bd/entidades/ArchivoCompartirConUsuarios.h"

namespace Test
{

class ArchivoCompartirConUsuarioTest : public testing::Test
{
public:

	static const std::string archivoEjemplo;

	ArchivoCompartirConUsuarioTest();
	virtual ~ArchivoCompartirConUsuarioTest();

	void testSetYGetAtributosCorrectamente();
	void testMetodosEntidad();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::ArchivoCompartirConUsuarios* archivoCompartir;
};
TEST_F(ArchivoCompartirConUsuarioTest, setYGetAtributos)
{
	ArchivoCompartirConUsuarioTest test;
	test.testSetYGetAtributosCorrectamente();
}
TEST_F(ArchivoCompartirConUsuarioTest, metodosEntidad)
{
	ArchivoCompartirConUsuarioTest test;
	test.testMetodosEntidad();
}
};

#endif /* ARCHIVOCOMPARTIRCONUSUARIOTEST_H_ */
