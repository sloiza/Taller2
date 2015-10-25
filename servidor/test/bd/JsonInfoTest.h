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
	void testGetValorPorDefaultCorrecto();

	void TestBody() {};
protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void finishing();

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

TEST_F(JsonInfoTest, valorPorDefaultCorrecto)
{
	JsonInfoTest test;
	test.testGetValorPorDefaultCorrecto();
}

};
#endif /* JSONINFOTEST_H_ */
