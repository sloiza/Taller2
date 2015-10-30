/*
 * URITest.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef URITEST_H_
#define URITEST_H_

// gtest
#include <gtest/gtest.h>

// conexion
#include "../../src/conexion/request/URI.h"

namespace Test

{

class URITest : public testing::Test {
public:
	URITest();
	virtual ~URITest();

	void testDividirUriVacia();
	void testDividirUriSinQuery();
	void testDividirUriConQuery();

	void TestBody() {};

protected:

	virtual void SetUp() {};
	virtual void TearDown() {};

	void setUp();
	void terminando();

	ConexionServidor::Request::URI* uri;
};

TEST_F(URITest, DividirUriVacia)
{
	URITest test;
	test.testDividirUriVacia();
}
TEST_F(URITest, DividirUriSinQuery)
{
	URITest test;
	test.testDividirUriSinQuery();
}
TEST_F(URITest, DividirUriConQuery)
{
	URITest test;
	test.testDividirUriConQuery();
}

}

#endif /* URITEST_H_ */
