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

namespace Test
{

class CreadorDeOperacionesTest : public testing::Test
{
public:

	CreadorDeOperacionesTest();
	virtual ~CreadorDeOperacionesTest();

	void testReconocerOperacionPrincipalCorrectamente();
	void testReconocerOperacionUsuariosCorrectamente();
	void testReconocerOperacionArchivosCorrectamente();
	void testReconocerOperacionCarpetasCorrectamente();
	void testReconocerOperacionCompartirArchivoCorrectamente();
	void testReconocerOperacionCompartirCarpetaCorrectamente();
	void testReconocerOperacionDescargarCorrectamente();
	void testDevolverOperacionErrorCuandoNoSeEncuentraRecurso();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	static ConexionServidor::Operaciones::CreadorDeOperaciones* creador;
	ConexionServidor::Request::URI* uri;

	static bool testEjecutados;
};

TEST_F(CreadorDeOperacionesTest, ReconocerOperacionPrincipal)
{
	CreadorDeOperacionesTest test;
	test.testReconocerOperacionPrincipalCorrectamente();
}
TEST_F(CreadorDeOperacionesTest, ReconocerOperacionUsuarios)
{
	CreadorDeOperacionesTest test;
	test.testReconocerOperacionUsuariosCorrectamente();
}
TEST_F(CreadorDeOperacionesTest, ReconocerOperacionArchivos)
{
	CreadorDeOperacionesTest test;
	test.testReconocerOperacionArchivosCorrectamente();
}
TEST_F(CreadorDeOperacionesTest, ReconocerOperacionCarpetas)
{
	CreadorDeOperacionesTest test;
	test.testReconocerOperacionCarpetasCorrectamente();
}
TEST_F(CreadorDeOperacionesTest, ReconocerOperacionCompartirArchivo)
{
	CreadorDeOperacionesTest test;
	test.testReconocerOperacionCompartirArchivoCorrectamente();
}
TEST_F(CreadorDeOperacionesTest, ReconocerOperacionCompartirCarpeta)
{
	CreadorDeOperacionesTest test;
	test.testReconocerOperacionCompartirCarpetaCorrectamente();
}
TEST_F(CreadorDeOperacionesTest, ReconocerOperacionDescargar)
{
	CreadorDeOperacionesTest test;
	test.testReconocerOperacionDescargarCorrectamente();
}
TEST_F(CreadorDeOperacionesTest, DevolverError)
{
	CreadorDeOperacionesTest test;
	test.testDevolverOperacionErrorCuandoNoSeEncuentraRecurso();
}

}

#endif /* CREADORDEOPERACIONESTEST_H_ */
