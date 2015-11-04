/*
 * JsonInfoTest.h
 *
 *  Created on: 12/10/2015
 *      Author: manuel
 */

#ifndef JSONINFOTEST_H_
#define JSONINFOTEST_H_

// gtest
#include <gtest/gtest.h>

// Base de datos
#include "../../src/bd/JsonInfo.h"

namespace Test
{

class JsonInfoTest : public testing::Test {
public:
	JsonInfoTest();
	virtual ~JsonInfoTest();

	static const std::string jsonEjemplo;

	void testCrearCorrectamente();
	void testContenidoNoValido();
	void testGetCampoBien();
	void testSettearYRecuperarCampoCorrectamente();
	void testAgregarValoresYRecuperarListaDeValoresCorrectamente();
	void testBorrarValorDeListaCorrectamente();

	void testGetValorPorDefaultCorrecto();
	void testCambiarContenidoCorrectamente();

	void TestBody() {};
protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::JsonInfo* info;

};

TEST_F(JsonInfoTest, creacionCorrecta)
{
	JsonInfoTest test;
	test.testCrearCorrectamente();
}
TEST_F(JsonInfoTest, contenidoNoValido)
{
	JsonInfoTest test;
	test.testContenidoNoValido();
}
TEST_F(JsonInfoTest, getCampoBien)
{
	JsonInfoTest test;
	test.testGetCampoBien();
}
TEST_F(JsonInfoTest, settearYRecuperarBien)
{
	JsonInfoTest test;
	test.testSettearYRecuperarCampoCorrectamente();
}
TEST_F(JsonInfoTest, agregarValoresYRecuperarListaDeValores)
{
	JsonInfoTest test;
	test.testAgregarValoresYRecuperarListaDeValoresCorrectamente();
}
TEST_F(JsonInfoTest, borrarValorDeListaDeValores)
{
	JsonInfoTest test;
	test.testBorrarValorDeListaCorrectamente();
}
TEST_F(JsonInfoTest, valorPorDefaultCorrecto)
{
	JsonInfoTest test;
	test.testGetValorPorDefaultCorrecto();
}
TEST_F(JsonInfoTest, cambiarContenidoCorrectamente)
{
	JsonInfoTest test;
	test.testCambiarContenidoCorrectamente();
}

};
#endif /* JSONINFOTEST_H_ */
