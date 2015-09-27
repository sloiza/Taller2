/*
 * ConexionTest.cpp
 *
 *  Created on: 25/9/2015
 *      Author: manuel
 */

#include "ConexionTest.h"

using namespace Tests;

ConexionTest::ConexionTest() : servidor(NULL) {}

ConexionTest::~ConexionTest() {}

void ConexionTest::SetUp()
{
	servidor = new ConexionServidor::Servidor();
	servidor->crear();
}

void ConexionTest::TearDown()
{
	servidor->destruir();
	delete servidor;
}

void ConexionTest::testConexionEstable()
{
	//int numConexiones = servidor->correr(1000);
	bool estaCorriendo = servidor->estaCorriendo();
	//EXPECT_NE(0, numConexiones);
	EXPECT_EQ(true, estaCorriendo);
}
