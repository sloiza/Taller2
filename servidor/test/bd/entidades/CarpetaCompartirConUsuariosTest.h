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
#include "../../../src/bd/entidades/CarpetaLogica.h"

namespace Test
{

class CarpetaCompartirConUsuariosTest : public testing::Test
{

public:
	CarpetaCompartirConUsuariosTest();
	virtual ~CarpetaCompartirConUsuariosTest();

	static const std::string compartirEjemplo;

	void testRecuperarCarpetaCorrectamente();
	void testRecuperarUsuariosCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::CarpetaCompartirConUsuarios* carpetaCompartir;
};

TEST_F(CarpetaCompartirConUsuariosTest, recuperarCarpeta)
{
	CarpetaCompartirConUsuariosTest test;
	test.testRecuperarCarpetaCorrectamente();
}
TEST_F(CarpetaCompartirConUsuariosTest, recuperarUsuarios)
{
	CarpetaCompartirConUsuariosTest test;
	test.testRecuperarUsuariosCorrectamente();
}
};


#endif /* CARPETACOMPARTIRCONUSUARIOSTEST_H_ */
