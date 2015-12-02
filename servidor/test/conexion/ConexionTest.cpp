/*
 * ConexionTest.cpp
 *
 *  Created on: 25/9/2015
 *      Author: manuel
 */

#include "ConexionTest.h"

using namespace Tests;

std::string ConexionTest::testUri = "uri/para/testear";;
std::string ConexionTest::testContenido = "1234567890";
std::string ConexionTest::testContenidoRelleno = "_contenidoDeRelleno";
std::string ConexionTest::testMetodo = "GET";
std::string ConexionTest::testQuery  = "queryDePrueba";

ConexionTest::ConexionTest() : servidor(NULL) , conexion(NULL)
{
	servidor = new ConexionServidor::Servidor();
	servidor->crear();

	servidorMT = new ConexionServidor::ServidorMultihilo();
	servidorMT->setPuerto(8080);
	servidorMT->setNumeroDeHilos(3);
	servidorMT->crear();

	struct mg_connection* conn = new struct mg_connection;

	std::string contenidoTotal = testContenido + testContenidoRelleno;
	char* buffer = new char[contenidoTotal.length() + 1];
	strcpy(buffer, contenidoTotal.c_str());

	conn->uri = testUri.c_str();
	conn->request_method = testMetodo.c_str();
	conn->content = buffer;
	conn->query_string = testQuery.c_str();
	conn->content_len = testContenido.size();

	conexion = new ConexionServidor::Conexion();
	conexion->inicializar(conn);

	delete conn;
	delete buffer;
}

ConexionTest::~ConexionTest()
{
	servidor->destruir();
	delete servidor;
	delete conexion;
}

void ConexionTest::SetUp() {}

void ConexionTest::TearDown() {}

void ConexionTest::testConexionEstable()
{
	int numConexiones = servidor->escuchar(1000);
	bool estaCorriendo = servidor->estaCorriendo();

	EXPECT_NE(0, numConexiones);
	EXPECT_EQ(true, estaCorriendo);

	estaCorriendo = servidorMT->estaCorriendo();

	EXPECT_EQ(true, estaCorriendo);
	EXPECT_STREQ("ServidorMultihilo", servidorMT->nombreClase().c_str() );
}

void ConexionTest::testInicializacionCorrecta()
{
	EXPECT_STREQ(testUri.c_str(), conexion->getUri()->getURI().c_str());
	EXPECT_STREQ(testMetodo.c_str(), conexion->getMetodo()->impresion().c_str());
	EXPECT_STREQ(testQuery.c_str(), conexion->getQuery().c_str());
	EXPECT_STREQ(testContenido.c_str(), conexion->getContenido().c_str());
	EXPECT_STREQ(testContenido.c_str(), conexion->getContenidoBytes()->getStringDeBytes().c_str());
}

void ConexionTest::testDevuelveGETComoMetodoDefault()
{
	struct mg_connection* conn = new struct mg_connection;

	conn->uri = testUri.c_str();
	conn->request_method = "metodoInvalido";
	conn->content = (char*)(testContenido + testContenidoRelleno).c_str();
	conn->query_string = testQuery.c_str();
	conn->content_len = testContenido.size();

	ConexionServidor::Conexion conex;
	conex.inicializar(conn);

	EXPECT_STREQ("GET", conex.getMetodo()->impresion().c_str());
}
