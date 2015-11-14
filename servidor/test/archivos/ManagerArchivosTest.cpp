/*
 * ManagerArchivosTest.cpp
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#include "ManagerArchivosTest.h"

using namespace Test;

Utiles::Bytes* ManagerArchivosTest::bytesEjemplo = new Utiles::Bytes("estosSonBytesDePrueba", 21);

ManagerArchivosTest::ManagerArchivosTest() : manager(NULL)
{
	this->setUp();
}

ManagerArchivosTest::~ManagerArchivosTest()
{
	this->terminando();
}

void ManagerArchivosTest::testEscribirYLeerEnDiscoCorrectamente()
{
	std::string path = "tmp/prueba1.test";
	this->manager->eliminar(path); // borro archivo generado por previos testeos

	this->manager->escribir(path, bytesEjemplo);
	Utiles::Bytes* bytesLeidos = this->manager->leer(path);

	EXPECT_STREQ(bytesEjemplo->getStringDeBytes().c_str(), bytesLeidos->getStringDeBytes().c_str());

	delete bytesLeidos;
}

void ManagerArchivosTest::testModificarEnDiscoCorrectamente()
{
	std::string path = "tmp/prueba2.test";
	this->manager->eliminar(path); // borro archivo generado por previos testeos

	this->manager->escribir(path, bytesEjemplo);
	Utiles::Bytes* bytesLeidos = this->manager->leer(path);

	EXPECT_STREQ(bytesEjemplo->getStringDeBytes().c_str(), bytesLeidos->getStringDeBytes().c_str());

	Utiles::Bytes* nuevosBytes = new Utiles::Bytes("estosSonNuevosBytes", 19);
	this->manager->modificar(path, nuevosBytes);
	Utiles::Bytes* nuevosBytesLeidos = this->manager->leer(path);

	EXPECT_STREQ("estosSonNuevosBytes", nuevosBytesLeidos->getStringDeBytes().c_str());

	delete bytesLeidos;
	delete nuevosBytes;
	delete nuevosBytesLeidos;
}

void ManagerArchivosTest::testEliminarDeDiscoCorrectamente()
{
	std::string path = "prueba3.test";

	this->manager->escribir(path, bytesEjemplo);
	Utiles::Bytes* bytesLeidos = this->manager->leer(path);

	EXPECT_STREQ(bytesEjemplo->getStringDeBytes().c_str(), bytesLeidos->getStringDeBytes().c_str());

	this->manager->eliminar(path);
	Utiles::Bytes* bytesVacios = this->manager->leer(path);

	EXPECT_EQ(NULL, bytesVacios);

	delete bytesLeidos;
	delete bytesVacios;
}

void ManagerArchivosTest::testCrearYEliminarCarpetaEnDiscoCorrectamente()
{
	std::string path = "tmp/carpetaManagerTest";

	EXPECT_EQ( false, manager->existe( path ));

	manager->crearCarpeta("tmp/", "carpetaManagerTest");

	EXPECT_EQ( true, manager->existe( path ));

	manager->eliminarCarpetaVacia("tmp/", "carpetaManagerTest");

	EXPECT_EQ( false, manager->existe( path ));
}

void ManagerArchivosTest::testEliminarCarpetaDeDiscoCorrectamente()
{

}

void ManagerArchivosTest::testChequeaQueHayContenidoEnCarpetaCorrecamente()
{
	std::string pathVacio = "tmp/carpetaVacia";

	EXPECT_EQ(true , manager->carpetaEstaVacia( pathVacio )); // VER PORQ NO FUNCA !!!!!!!!

	std::string pathConContenido = "tmp/";

	EXPECT_EQ(false , manager->carpetaEstaVacia( pathConContenido));
}

void ManagerArchivosTest::setUp()
{
	this->manager = new ConexionServidor::BaseDeDatos::ManagerArchivos();
}

void ManagerArchivosTest::terminando()
{
	if ( this->manager != NULL )
	{
		delete this->manager;
		this->manager = NULL;
	}
}
