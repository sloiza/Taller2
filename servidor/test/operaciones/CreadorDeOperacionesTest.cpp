/*
 * CreadorDeOperacionesTest.cpp
 *
 *  Created on: 29/10/2015
 *      Author: manuel
 */

#include "CreadorDeOperacionesTest.h"

using namespace Test;

ConexionServidor::Operaciones::CreadorDeOperaciones* CreadorDeOperacionesTest::creador = NULL;
bool CreadorDeOperacionesTest::testEjecutados = false;

CreadorDeOperacionesTest::CreadorDeOperacionesTest() : uri(NULL)
{
	this->setUp();
}

CreadorDeOperacionesTest::~CreadorDeOperacionesTest()
{
	this->terminando();
}

void CreadorDeOperacionesTest::testReconocerOperacionPrincipalCorrectamente()
{
	std::string uriPrincipal = "/";
	this->uri->setURI(uriPrincipal);

	ConexionServidor::Operaciones::IOperable* operacion = this->creador->getOperacion(this->uri);
	operacion->imprimir();
	//std::cout << "operacion: " << operacion->imprimir() << "\n";

	//EXPECT_STREQ("principal", operacion->imprimir().c_str());
}
void CreadorDeOperacionesTest::testReconocerOperacionUsuariosCorrectamente()
{
	std::string uriUsuarios = "/usuario";
	this->uri->setURI(uriUsuarios);

	ConexionServidor::Operaciones::IOperable* operacion = this->creador->getOperacion(this->uri);
	operacion->imprimir();
	//EXPECT_STREQ("usuarios", operacion->imprimir().c_str());
}
void CreadorDeOperacionesTest::testReconocerOperacionArchivosCorrectamente()
{
	std::string uriArchivos = "/usuario/miBaul";
	this->uri->setURI(uriArchivos);

	ConexionServidor::Operaciones::IOperable* operacion = this->creador->getOperacion(this->uri);
	operacion->imprimir();
	//EXPECT_STREQ("archivos", operacion->imprimir().c_str());
}
void CreadorDeOperacionesTest::testReconocerOperacionCarpetasCorrectamente()
{
	std::string uriCarpeta = "/usuario/miBaul/misCarpetas";
	this->uri->setURI(uriCarpeta);

	ConexionServidor::Operaciones::IOperable* operacion = this->creador->getOperacion(this->uri);
	operacion->imprimir();
	//EXPECT_STREQ("carpetas", operacion->imprimir().c_str());
}
void CreadorDeOperacionesTest::testReconocerOperacionCompartirArchivoCorrectamente()
{
	std::string uriCompartirArchivo = "/usuario/miBaul?compartirArchivo=archivo.txt";
	this->uri->setURI(uriCompartirArchivo);

	ConexionServidor::Operaciones::IOperable* operacion = this->creador->getOperacion(this->uri);
	operacion->imprimir();
	//EXPECT_STREQ("compartirArchivo", operacion->imprimir().c_str());
}
void CreadorDeOperacionesTest::testReconocerOperacionCompartirCarpetaCorrectamente()
{
	std::string uriCompartirCarpeta = "/usuario/miBaul?compartirCarpeta=carpeta";
	this->uri->setURI(uriCompartirCarpeta);

	ConexionServidor::Operaciones::IOperable* operacion = this->creador->getOperacion(this->uri);
	operacion->imprimir();
	//EXPECT_STREQ("compartirCarpeta", operacion->imprimir().c_str());
}
void CreadorDeOperacionesTest::testReconocerOperacionDescargarCorrectamente()
{
	std::string uriDescarga = "/usuario/miBaul?descargar=archivo.txt";
	this->uri->setURI(uriDescarga);

	ConexionServidor::Operaciones::IOperable* operacion = this->creador->getOperacion(this->uri);
	operacion->imprimir();
	//EXPECT_STREQ("descargar", operacion->imprimir().c_str());
}
void CreadorDeOperacionesTest::testDevolverOperacionErrorCuandoNoSeEncuentraRecurso()
{
	std::string uriError = "/uri/no/mapeada";
	this->uri->setURI(uriError);

	ConexionServidor::Operaciones::IOperable* operacion = this->creador->getOperacion(this->uri);
	operacion->imprimir();
	//EXPECT_STREQ("error", operacion->imprimir().c_str());

	testEjecutados = true;
}

void CreadorDeOperacionesTest::setUp()
{
	if ( creador == NULL )
	{
		creador = new ConexionServidor::Operaciones::CreadorDeOperaciones();
		creador->crearArbolDeRecursos();
	}

	this->uri = new ConexionServidor::Request::URI();
}
void CreadorDeOperacionesTest::terminando()
{
	if ( testEjecutados == false )
	{
		return;
	}

	if ( this->creador != NULL )
	{
		this->creador->liberarArbolDeRecursos();
		delete this->creador;
		this->creador = NULL;
	}

	if ( this->uri != NULL )
	{
		delete this->uri;
		this->uri = NULL;
	}
}
