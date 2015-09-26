/*
 * ConexionTest.h
 *
 *  Created on: 25/9/2015
 *      Author: manuel
 */

#ifndef CONEXIONTEST_H_
#define CONEXIONTEST_H_

// Test
#include <gtest/gtest.h>

// Conexion
#include "../../src/conexion/Servidor.h"

namespace Tests
{

class ConexionTest : public testing::Test {

public:
	ConexionTest();
	virtual ~ConexionTest();

	void testConexionEstable();

	void TestBody() {};
protected:

	virtual void SetUp();
	virtual void TearDown();

	ConexionServidor::Servidor* servidor;
};

TEST_F(ConexionTest, ConexionEstable)
{
	ConexionTest conexionTest;
	conexionTest.testConexionEstable();
}

};

#endif /* CONEXIONTEST_H_ */
