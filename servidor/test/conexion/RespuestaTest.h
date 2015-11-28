/*
 * RespuestaTest.h
 *
 *  Created on: 28/11/2015
 *      Author: manuel
 */

#ifndef RESPUESTATEST_H_
#define RESPUESTATEST_H_

// Test
#include <gtest/gtest.h>

// Conexion
#include "../../src/conexion/Respuesta.h"

namespace Test
{

class RespuestaTest : public testing::Test
{
public:
	RespuestaTest();
	virtual ~RespuestaTest();

	void TestBody() {};

	void testSetYGetAtributosCorrectamente();

protected:

	virtual void SetUp(){};
	virtual void TearDown(){};
};
TEST_F(RespuestaTest , setYGetAtributos)
{
	RespuestaTest test;
	test.testSetYGetAtributosCorrectamente();
}

};

#endif /* RESPUESTATEST_H_ */
