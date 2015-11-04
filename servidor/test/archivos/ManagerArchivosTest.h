/*
 * ManagerArchivosTest.h
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#ifndef MANAGERARCHIVOSTEST_H_
#define MANAGERARCHIVOSTEST_H_

// gtest
#include <gtest/gtest.h>

// Manager
#include "../../src/archivos/ManagerArchivos.h"

// utiles
#include "../../src/utiles/Bytes.h"

namespace Test
{

class ManagerArchivosTest : public testing::Test
{
public:
	ManagerArchivosTest();
	virtual ~ManagerArchivosTest();

	static Utiles::Bytes* bytesEjemplo;

	void testEscribirYLeerEnDiscoCorrectamente();
	void testModificarEnDiscoCorrectamente();
	void testEliminarDeDiscoCorrectamente();

	void testCrearYEliminarCarpetaEnDiscoCorrectamente();
	void testEliminarCarpetaDeDiscoCorrectamente();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::BaseDeDatos::ManagerArchivos* manager;
};

TEST_F(ManagerArchivosTest, escribirYLeerEnDisco)
{
	ManagerArchivosTest test;
	test.testEscribirYLeerEnDiscoCorrectamente();
}
TEST_F(ManagerArchivosTest, modificarEnDisco)
{
	ManagerArchivosTest test;
	test.testModificarEnDiscoCorrectamente();
}
TEST_F(ManagerArchivosTest, eliminarDeDisco)
{
	ManagerArchivosTest test;
	test.testEliminarDeDiscoCorrectamente();
}
TEST_F(ManagerArchivosTest, crearYEliminarCarpeta)
{
	ManagerArchivosTest test;
	test.testCrearYEliminarCarpetaEnDiscoCorrectamente();
}


};

#endif /* MANAGERARCHIVOSTEST_H_ */
