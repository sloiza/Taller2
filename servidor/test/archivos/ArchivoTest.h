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

namespace Test
{

class ArchivoTest : public testing::Test
{
public:
	ArchivoTest();
	virtual ~ArchivoTest();

	static const char bytes[];

	void testGuardarArchivoCorrectamente();
	void testModificarArchivoCorrectamente();
	void testRecuperarArchivoCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::Archivo* archivo;
};
};

#endif /* ARCHIVOTEST_H_ */
