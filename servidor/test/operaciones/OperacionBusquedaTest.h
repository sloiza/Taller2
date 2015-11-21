/*
 * OperacionBusquedaTest.h
 *
 *  Created on: 18/11/2015
 *      Author: manuel
 */

#ifndef OPERACIONBUSQUEDATEST_H_
#define OPERACIONBUSQUEDATEST_H_

// gtest
#include <gtest/gtest.h>

// operaciones
#include "../../src/operaciones/OperacionBusqueda.h"

namespace Test
{

class OperacionBusquedaTest : public testing::Test
{
public:
	OperacionBusquedaTest();
	virtual ~OperacionBusquedaTest();

	static const std::string archivoEjemplo1;
	static const std::string archivoEjemplo2;
	static const std::string archivoEjemplo3;
	static const std::string archivoEjemplo4;
	static const std::string archivoEjemplo5;
	static const std::string archivoEjemplo6;

	void testBuscarPorNombreCorrectamente();
	void testBuscarPorEtiquetaCorrectamente();
	void testBuscarPorExtensionCorrectamente();
	void testBuscarPorPropietarioCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::Operaciones::OperacionBusqueda* buscador;
	std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> listaArchivos;
};
TEST_F(OperacionBusquedaTest, buscarPorNombre)
{
	OperacionBusquedaTest test;
	test.testBuscarPorNombreCorrectamente();
}
TEST_F(OperacionBusquedaTest, buscarPorEtiqueta)
{
	OperacionBusquedaTest test;
	test.testBuscarPorEtiquetaCorrectamente();
}
TEST_F(OperacionBusquedaTest, buscarPorExtension)
{
	OperacionBusquedaTest test;
	test.testBuscarPorExtensionCorrectamente();
}
TEST_F(OperacionBusquedaTest, buscarPorPropietario)
{
	OperacionBusquedaTest test;
	test.testBuscarPorPropietarioCorrectamente();
}
};

#endif /* OPERACIONBUSQUEDATEST_H_ */
