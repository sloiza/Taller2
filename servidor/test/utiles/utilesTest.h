/*
 * utilesTest.h
 *
 *  Created on: 26/11/2015
 *      Author: manuel
 */

#ifndef UTILESTEST_H_
#define UTILESTEST_H_
// gtest
#include <gtest/gtest.h>

// manager archivos
#include "../../src/archivos/ManagerArchivos.h"

// utiles
#include "../../src/utiles/base64.h"
#include "../../src/utiles/utiles.h"
#include "../../src/utiles/Log.h"
#include "../../src/utiles/LectorParametros.h"

namespace Test
{

class utilesTest : public testing::Test
{
public:
	utilesTest();
	virtual ~utilesTest();

	void testSplitCorrectamente();
	void testCodearYEncodearBase64Correctamente();
	void testCrearLogsCorrectamente();
	void testLectorLeeParametrosCorrectamente();


	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};
};

TEST_F(utilesTest, split)
{
	utilesTest test;
	test.testSplitCorrectamente();
}
TEST_F(utilesTest, base64)
{
	utilesTest test;
	test.testCodearYEncodearBase64Correctamente();
}
TEST_F(utilesTest, logs)
{
	utilesTest test;
	test.testCrearLogsCorrectamente();
}
//TEST_F(utilesTest, lectorDeParametros)
//{
//	utilesTest test;
//	test.testLectorLeeParametrosCorrectamente();
//}
};

#endif /* UTILESTEST_H_ */
