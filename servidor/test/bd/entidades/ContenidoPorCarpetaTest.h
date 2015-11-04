/*
 * ContenidoPorCarpetaTest.h
 *
 *  Created on: 4/11/2015
 *      Author: manuel
 */

#ifndef CONTENIDOPORCARPETATEST_H_
#define CONTENIDOPORCARPETATEST_H_

// gtest
#include <gtest/gtest.h>

// User
#include "../../../src/bd/entidades/ContenidoPorCarpeta.h"

namespace Test
{

class ContenidoPorCarpetaTest : public testing::Test
{
public:
	ContenidoPorCarpetaTest();
	virtual ~ContenidoPorCarpetaTest();

	static const std::string contenidoEjemplo;

	void testCrearYRecuperarEnBDCorrectamente();
	void testModificarEnBDCorrectamente();
	void testEliminarEnBDCorrectamente();
	void testDevolvePathCorrecto();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido;
};

TEST_F(ContenidoPorCarpetaTest, crearYRecuperarEnBD)
{
	ContenidoPorCarpetaTest test;
	test.testCrearYRecuperarEnBDCorrectamente();
}
TEST_F(ContenidoPorCarpetaTest, modificarEnBD)
{
	ContenidoPorCarpetaTest test;
	test.testModificarEnBDCorrectamente();
}
TEST_F(ContenidoPorCarpetaTest, eliminarEnBD)
{
	ContenidoPorCarpetaTest test;
	test.testEliminarEnBDCorrectamente();
}
TEST_F(ContenidoPorCarpetaTest, devolverPath)
{
	ContenidoPorCarpetaTest test;
	test.testDevolvePathCorrecto();
}

};

#endif /* CONTENIDOPORCARPETATEST_H_ */
