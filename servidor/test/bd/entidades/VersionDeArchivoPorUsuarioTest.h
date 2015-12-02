/*
 * VersionDeArchivoPorUsuarioTest.h
 *
 *  Created on: 28/11/2015
 *      Author: manuel
 */

#ifndef VERSIONDEARCHIVOPORUSUARIOTEST_H_
#define VERSIONDEARCHIVOPORUSUARIOTEST_H_

// gtest
#include <gtest/gtest.h>

// User
#include "../../../src/bd/entidades/VersionDeArchivoPorUsuario.h"

namespace Test
{

class VersionDeArchivoPorUsuarioTest : public testing::Test
{
public:
	VersionDeArchivoPorUsuarioTest();
	virtual ~VersionDeArchivoPorUsuarioTest();

	void testSetYGetAtributos();
	void testMetodosEntidad();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

};
TEST_F(VersionDeArchivoPorUsuarioTest, setYGetAtributos)
{
	VersionDeArchivoPorUsuarioTest test;
	test.testSetYGetAtributos();

}
TEST_F(VersionDeArchivoPorUsuarioTest, metodosEntidad)
{
	VersionDeArchivoPorUsuarioTest test;
	test.testMetodosEntidad();
}
};
#endif /* VERSIONDEARCHIVOPORUSUARIOTEST_H_ */
