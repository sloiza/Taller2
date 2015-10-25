/*
 * ManagerBDTest.cpp
 *
 *  Created on: 12/10/2015
 *      Author: manuel
 */

#include "ManagerBDTest.h"

using namespace Test;

ManagerBDTest::ManagerBDTest() : manager(NULL) {}

ManagerBDTest::~ManagerBDTest() {}

void ManagerBDTest::testInicializadaYCerradaCorrectamente()
{
	this->manager = new ConexionServidor::BaseDeDatos::ManagerBD();

	EXPECT_EQ(false, this->manager->estaAbierta());

	this->manager->inicializar();

	EXPECT_EQ(true, this->manager->estaAbierta());

	this->manager->cerrar();

	EXPECT_EQ(false, this->manager->estaAbierta());

	delete this->manager;
}

void ManagerBDTest::testInsertarYRecuperarRegistro()
{
	this->manager = new ConexionServidor::BaseDeDatos::ManagerBD();
	this->manager->inicializar();

	this->manager->insertar(clave, "valor");

	std::string valorRecuperado = this->manager->recuperar(clave);

	EXPECT_STREQ("valor", valorRecuperado.c_str());

	delete this->manager;
}

void ManagerBDTest::testEliminarRegistro()
{
	EXPECT_EQ(true, true);
}
