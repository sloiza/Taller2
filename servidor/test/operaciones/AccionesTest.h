/*
 * AccionesTest.h
 *
 *  Created on: 21/11/2015
 *      Author: manuel
 */

#ifndef ACCIONESTEST_H_
#define ACCIONESTEST_H_

// gtest
#include <gtest/gtest.h>

// operaciones
#include "../../src/archivos/Archivo.h"
#include "../../src/bd/entidades/ArchivoLogico.h"
#include "../../src/operaciones/Acciones.h"

namespace Test
{

class AccionesTest : public testing::Test
{
public:
	AccionesTest();
	virtual ~AccionesTest();

	static const std::string archivoEjemplo;
	static char bytes[];
	static const int tamanio = 25;

	void testAltaLogicaArchivoCorrectamente();
	void testAltaFisicaArchivoCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::Archivo* archivoFisico;
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico;
	ConexionServidor::Operaciones::Acciones acciones;
};
TEST_F(AccionesTest, altaLogica)
{
	AccionesTest test;
	test.testAltaLogicaArchivoCorrectamente();
}
TEST_F(AccionesTest, altaFisica)
{
	AccionesTest test;
	test.testAltaFisicaArchivoCorrectamente();
}
};

#endif /* ACCIONESTEST_H_ */
