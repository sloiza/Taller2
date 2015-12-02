/*
 * ArchivoLogicoTest.cpp
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#include "ArchivoLogicoTest.h"

using namespace Test;

ArchivoLogicoTest::ArchivoLogicoTest() : archivo(NULL)
{
	this->setUp();
}

ArchivoLogicoTest::~ArchivoLogicoTest()
{
	this->terminando();
}

const std::string ArchivoLogicoTest::archivoEjemplo =
"{\"nombre\":\"foto_09082015\",\"extension\":\"jpg\",\"etiqueta\": [ \"imagen\" ], \"fecha_ulti_modi\":\"26102015\","
"\"usuario_ulti_modi\":\"1234\", \"propietario\":\"1234\", \"baja_logica\":\"no\", \"compartido_con\": [ \"arturito\"] , \"version\": \"1\" }";

void ArchivoLogicoTest::testCrearYRecuperarEnBDCorrectamente()
{
	this->archivo->guardar();

	std::string contenidoRecuperado = this->archivo->recuperar();

	ConexionServidor::BaseDeDatos::ArchivoLogico archivoRecuperado;
	archivoRecuperado.setContenido(contenidoRecuperado);

	EXPECT_STREQ(this->archivo->getContenido().c_str(), archivoRecuperado.getContenido().c_str());
}

void ArchivoLogicoTest::testModificarEnBDCorrectamente()
{
	this->archivo->guardar();

	EXPECT_STREQ("foto_09082015", this->archivo->getNombre().c_str());
	EXPECT_STREQ("jpg", this->archivo->getExtension().c_str());

	this->archivo->setNombre("foto_26102015");
	this->archivo->setExtension("png");
	this->archivo->agregarEtiqueta( "foto" );
	this->archivo->setUltimaFechaModif( "20151128" );
	this->archivo->setUltimoUsuarioModif( "changos" );
	this->archivo->setPropietario( "elpropi" );
	this->archivo->agregarCompartidoCon( "rober@gmail.com" );
	this->archivo->setVersion( "2" );

	this->archivo->modificar();

	std::string contenidoNuevo = this->archivo->recuperar();

	ConexionServidor::BaseDeDatos::ArchivoLogico archivoNuevo;
	archivoNuevo.setContenido(contenidoNuevo);

	EXPECT_STREQ("foto_26102015", archivoNuevo.getNombre().c_str());
	EXPECT_STREQ("png", archivoNuevo.getExtension().c_str());
	EXPECT_STREQ("foto", archivoNuevo.getEtiquetas()[1].c_str());
	EXPECT_STREQ("20151128", archivoNuevo.getUltimaFechaModif().c_str());
	EXPECT_STREQ("changos", archivoNuevo.getUltimoUsuarioModif().c_str());
	EXPECT_STREQ("elpropi", archivoNuevo.getPropietario().c_str());
	EXPECT_STREQ("rober@gmail.com", archivoNuevo.getCompartidoCon()[1].c_str());
	EXPECT_STREQ("2", archivoNuevo.getVersion().c_str());
	EXPECT_STREQ("foto_26102015.png", archivoNuevo.getNombreYExtension().c_str());
}

void ArchivoLogicoTest::testEliminarEnBDCorrectamente()
{

}

void ArchivoLogicoTest::testModificarAtributoCorrectamente()
{
	std::string nombre = this->archivo->getNombre();

	EXPECT_STREQ("foto_09082015", nombre.c_str());

	this->archivo->setNombre("foto_26102015");

	std::string nombreNuevo = this->archivo->getNombre();

	EXPECT_STREQ("foto_26102015", nombreNuevo.c_str());
}

void ArchivoLogicoTest::testSetearPathCorrectamente()
{
	this->archivo->setPath("esto/es/un/path/cualquier/archivo.txt");

	EXPECT_STREQ( "esto/es/un/path/cualquier/", archivo->getDireccion().c_str() );
	EXPECT_STREQ( "archivo", archivo->getNombre().c_str() );
	EXPECT_STREQ( "txt", archivo->getExtension().c_str() );

	this->archivo->setPath("esto/es/un/path/cualquier/archivo.con-extension+extrania.txt+[23");

	EXPECT_STREQ( "esto/es/un/path/cualquier/", archivo->getDireccion().c_str() );
	EXPECT_STREQ( "archivo.con-extension+extrania", archivo->getNombre().c_str() );
	EXPECT_STREQ( "txt+[23", archivo->getExtension().c_str() );
}

void ArchivoLogicoTest::setUp()
{
	this->archivo = new ConexionServidor::BaseDeDatos::ArchivoLogico(archivoEjemplo);
}

void ArchivoLogicoTest::terminando()
{
	if ( this->archivo != NULL )
	{
		delete this->archivo;
		this->archivo = NULL;
	}
}
