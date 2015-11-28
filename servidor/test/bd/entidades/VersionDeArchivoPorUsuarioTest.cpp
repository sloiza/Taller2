/*
 * VersionDeArchivoPorUsuarioTest.cpp
 *
 *  Created on: 28/11/2015
 *      Author: manuel
 */

#include "VersionDeArchivoPorUsuarioTest.h"

using namespace Test;

VersionDeArchivoPorUsuarioTest::VersionDeArchivoPorUsuarioTest() {}

VersionDeArchivoPorUsuarioTest::~VersionDeArchivoPorUsuarioTest() {}

void VersionDeArchivoPorUsuarioTest::testSetYGetAtributos()
{
	ConexionServidor::BaseDeDatos::VersionDeArchivoPorUsuario version;

	version.setUsuario( "manu@gmail.com" );
	version.setPathArchivo( "tmp/archivo.test" );
	version.setVersion( "1" );

	EXPECT_STREQ( "manu@gmail.com", version.getUsuario().c_str() );
	EXPECT_STREQ( "tmp/archivo.test", version.getPathArchivo().c_str() );
	EXPECT_STREQ( "1", version.getVersion().c_str() );
}
void VersionDeArchivoPorUsuarioTest::testMetodosEntidad()
{
	ConexionServidor::BaseDeDatos::VersionDeArchivoPorUsuario version;

	version.setUsuario( "manu@gmail.com" );
	version.setPathArchivo( "tmp/archivo.test" );
	version.setVersion( "1" );

	ConexionServidor::BaseDeDatos::VersionDeArchivoPorUsuario version2;

	version2.setContenido( version.getValor() );

	EXPECT_STREQ( "manu@gmail.com", version2.getUsuario().c_str() );
	EXPECT_STREQ( "tmp/archivo.test", version2.getPathArchivo().c_str() );
	EXPECT_STREQ( "1", version2.getVersion().c_str() );
}
