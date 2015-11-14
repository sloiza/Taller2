/*
 * CarpetaCompartirConUsuariosTest.h
 *
 *  Created on: 14/11/2015
 *      Author: manuel
 */

#ifndef CARPETACOMPARTIRCONUSUARIOSTEST_H_
#define CARPETACOMPARTIRCONUSUARIOSTEST_H_

// gtest
#include <gtest/gtest.h>

// User
#include "../../../src/bd/entidades/CarpetaCompartirConUsuarios.h"

namespace Test
{

class CarpetaCompartirConUsuariosTest : public testing::Test
{

public:
	CarpetaCompartirConUsuariosTest();
	virtual ~CarpetaCompartirConUsuariosTest();

	static const std::string archivoEjemplo;

	void testRecuperarCarpetaCorrectamente();
	void testRecuperarUsuariosCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::CarpetaCompartirConUsuarios* archivo;
};
};


#endif /* CARPETACOMPARTIRCONUSUARIOSTEST_H_ */
