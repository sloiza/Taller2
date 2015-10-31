/*
 * rocksdbTest.h
 *
 *  Created on: 10/10/2015
 *      Author: manuel
 */

#ifndef ROCKSDBTEST_H_
#define ROCKSDBTEST_H_

// Test
#include <gtest/gtest.h>

// Base de datos
#include "../../src/bd/rocks_db.h"

namespace Tests
{

class rocks_dbTest : public testing::Test {
public:
	rocks_dbTest();
	virtual ~rocks_dbTest();

	void inicializar();

	void testInsertarYRecuperarRegistro();
	void testEliminarRegistro();
	void testRecuperarRegistroInexistente();

	void TestBody() {};
protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	rocks_db* bd;
};

TEST_F(rocks_dbTest, InsertarYRecuperarRegistro)
{
	rocks_dbTest test;
	test.inicializar();
	test.testInsertarYRecuperarRegistro();
}
TEST_F(rocks_dbTest, EliminarRegistro)
{
//	rocks_dbTest test;
//	test.testEliminarRegistro();
}
TEST_F(rocks_dbTest, RecuperarInexistente)
{
	rocks_dbTest test;
	test.inicializar();
	test.testRecuperarRegistroInexistente();
}

};

#endif /* ROCKSDBTEST_H_ */
