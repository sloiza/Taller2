/*
 * UserTest.h
 *
 *  Created on: 25/10/2015
 *      Author: manuel
 */

#ifndef USERTEST_H_
#define USERTEST_H_

// gtest
#include <gtest/gtest.h>

// User
#include "../../../src/bd/entidades/User.h"

namespace Test {

class UserTest : public testing::Test {
public:
	UserTest();
	virtual ~UserTest();

	static const std::string usuarioEjemplo;

	void testCrearYRecuperarEnBDCorrectamente();
	void testModificarEnBDCorrectamente();
	void testEliminarEnBDCorrectamente();
	void testModificarAtributoCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::User* user;
};

TEST_F(UserTest, crearYRecuperarEnBD)
{
	UserTest test;
	test.testCrearYRecuperarEnBDCorrectamente();
}

TEST_F(UserTest, modificarEnBD)
{
	UserTest test;
	test.testModificarEnBDCorrectamente();
}

TEST_F(UserTest, eliminarEnBD)
{
	UserTest test;
	test.testEliminarEnBDCorrectamente();
}

TEST_F(UserTest, modificarAtributo)
{
	UserTest test;
	test.testModificarAtributoCorrectamente();
}

};

#endif /* USERTEST_H_ */
