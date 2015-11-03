/*
 * ArchivoTest.h
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#ifndef ARCHIVOTEST_H_
#define ARCHIVOTEST_H_

// gtest
#include <gtest/gtest.h>

// Archivo
#include "../../src/archivos/Archivo.h"
#include "../../src/archivos/ManagerArchivos.h"

// utiles
#include "../../src/utiles/Bytes.h"


namespace Test
{

class ArchivoTest : public testing::Test
{
public:
	ArchivoTest();
	virtual ~ArchivoTest();

	static char bytes[];
	static const int tamanio = 25;
	static const std::string archivoEjemplo1;
	static const std::string archivoEjemplo2;
	static const std::string archivoEjemplo3;

	void testSetYGetBytesCorrectamente();
	void testGuardarArchivoCorrectamente();
	void testModificarArchivoCorrectamente();
	void testRecuperarArchivoCorrectamente();
	void testEliminarArchivoCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::Archivo* archivo1;
	ConexionServidor::BaseDeDatos::ManagerArchivos manager;
};
TEST_F(ArchivoTest, SetYGetBytes)
{
	ArchivoTest test;
	test.testSetYGetBytesCorrectamente();
}
TEST_F(ArchivoTest, GuardarArchivo)
{
	ArchivoTest test;
	test.testGuardarArchivoCorrectamente();
}
TEST_F(ArchivoTest, ModificarArchivo)
{
	ArchivoTest test;
	test.testModificarArchivoCorrectamente();
}
TEST_F(ArchivoTest, RecuperarArchivo)
{
	ArchivoTest test;
	test.testRecuperarArchivoCorrectamente();
}
TEST_F(ArchivoTest, EliminarArchivo)
{
	ArchivoTest test;
	test.testEliminarArchivoCorrectamente();
}

};

#endif /* ARCHIVOTEST_H_ */
