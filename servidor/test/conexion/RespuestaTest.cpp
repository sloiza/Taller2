/*
 * RespuestaTest.cpp
 *
 *  Created on: 28/11/2015
 *      Author: manuel
 */

#include "RespuestaTest.h"

using namespace Test;

RespuestaTest::RespuestaTest() {}

RespuestaTest::~RespuestaTest() {}

void RespuestaTest::testSetYGetAtributosCorrectamente()
{
	ConexionServidor::Respuesta rta;

	rta.setEstado( "ok" );
	rta.setMensaje( "mensajito" );
	rta.setBytes( "bytes" );
	rta.setEsDescarga(false);
	rta.setPathDelArchivoADescargar("path/archivo.test");

	ConexionServidor::Respuesta rta2;
	rta2.setContenido( rta.getValor() );
	rta2.setPathDelArchivoADescargar( rta.getPathDelArchivoADescargar() );

	EXPECT_STREQ( "ok", rta2.getEstado().c_str() );
	EXPECT_STREQ( "mensajito", rta2.getMensaje().c_str() );
	EXPECT_STREQ( "bytes", rta2.getBytes().c_str() );
	EXPECT_EQ( false, rta2.getEsDescarga() );
	EXPECT_STREQ( "path/archivo.test", rta2.getPathDelArchivoADescargar().c_str() );
}
