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
#include "../../src/conexion/Conexion.h"
#include "../../src/utiles/Log.h"
#include "../../src/conexion/mongoose.h"
#include "../../src/conexion/Servidor.h"

namespace Tests
{

class ConexionTest : public testing::Test {

public:

	ConexionTest();
	virtual ~ConexionTest();

	static std::string testUri;
	static std::string testContenido;
	static std::string testContenidoRelleno;
	static std::string testMetodo;
	static std::string testQuery;

	void testConexionEstable();
	void testInicializacionCorrecta();
	void testDevuelveGETComoMetodoDefault();

	void TestBody() {};
protected:

	virtual void SetUp();
	virtual void TearDown();

	ConexionServidor::Servidor* servidor;
	ConexionServidor::Conexion* conexion;
};

TEST_F(ConexionTest, ConexionEstable)
{
	ConexionTest conexionTest;
	conexionTest.testConexionEstable();
}

TEST_F(ConexionTest, DevuelveGETComoMetodoDefault)
{
	ConexionTest conexionTest;
	conexionTest.testDevuelveGETComoMetodoDefault();
}

TEST_F(ConexionTest, InicializacionCorrecta)
{
	ConexionTest conexionTest;
	conexionTest.testInicializacionCorrecta();
}
};

#endif /* CONEXIONTEST_H_ */
