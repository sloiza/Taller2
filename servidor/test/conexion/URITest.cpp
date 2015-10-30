/*
 * URITest.cpp
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#include "URITest.h"

using namespace Test;

URITest::URITest() : uri(NULL)
{
	this->setUp();
}

URITest::~URITest()
{
	this->terminando();
}

void URITest::testDividirUriVacia()
{
	std::string uriVacia = "";
	this->uri->setURI(uriVacia);
	std::vector<std::string> recursos = this->uri->getRecursosDividos();

	EXPECT_EQ(0, recursos.size());
}
void URITest::testDividirUriSinQuery()
{
	std::string uriSinQuery = "usuario/miBaul";

	this->uri->setURI(uriSinQuery);
	std::vector<std::string> recursos = this->uri->getRecursosDividos();

	EXPECT_STREQ("usuario", recursos[0].c_str());
	EXPECT_STREQ("miBaul", recursos[1].c_str());

	EXPECT_EQ(2, recursos.size());

}
void URITest::testDividirUriConQuery()
{
	std::string uriConQuery = "usuario/miBaul?descargar=unArchivo.txt";

	this->uri->setURI(uriConQuery);
	std::vector<std::string> recursos = this->uri->getRecursosDividos();

	EXPECT_STREQ("usuario", recursos[0].c_str());
	EXPECT_STREQ("miBaul", recursos[1].c_str());
	EXPECT_STREQ("descargar", recursos[2].c_str());

	EXPECT_EQ(3, recursos.size());
}

void URITest::setUp()
{
	this->uri = new ConexionServidor::Request::URI();
}
void URITest::terminando()
{
	if ( this->uri != NULL )
	{
		delete this->uri;
		this->uri = NULL;
	}
}
