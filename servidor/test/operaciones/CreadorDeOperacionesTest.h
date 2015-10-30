/*
 * CreadorDeOperacionesTest.h
 *
 *  Created on: 29/10/2015
 *      Author: manuel
 */

#ifndef CREADORDEOPERACIONESTEST_H_
#define CREADORDEOPERACIONESTEST_H_

// gtest
#include <gtest/gtest.h>

// operaciones
#include "../../src/operaciones/CreadorDeOperaciones.h"

// STL

namespace Test
{

class CreadorDeOperacionesTest : public testing::Test
{
public:

	CreadorDeOperacionesTest();
	virtual ~CreadorDeOperacionesTest();

	void testDividirUriVacia();
	void testDividirUriSinQuery();
	void testDividirUriConQuery();
	void testReconocerOperacionesCorrectamente();
	void testDevolverErrorCuandoNoSeEncuentraRecurso();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::Operaciones::CreadorDeOperaciones* creador;
};

TEST_F(CreadorDeOperacionesTest, DividirUriVacia)
{
	CreadorDeOperacionesTest test;
	test.testDividirUriVacia();
}
TEST_F(CreadorDeOperacionesTest, DividirUriSinQuery)
{
	CreadorDeOperacionesTest test;
	test.testDividirUriSinQuery();
}
TEST_F(CreadorDeOperacionesTest, DividirUriConQuery)
{
	CreadorDeOperacionesTest test;
	test.testDividirUriConQuery();
}
TEST_F(CreadorDeOperacionesTest, ReconocerOperaciones)
{
	CreadorDeOperacionesTest test;
	test.testReconocerOperacionesCorrectamente();
}
TEST_F(CreadorDeOperacionesTest, DevolverError)
{
	CreadorDeOperacionesTest test;
	test.testDevolverErrorCuandoNoSeEncuentraRecurso();
}

}

#endif /* CREADORDEOPERACIONESTEST_H_ */
