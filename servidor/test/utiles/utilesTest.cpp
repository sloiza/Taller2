/*
 * utilesTest.cpp
 *
 *  Created on: 26/11/2015
 *      Author: manuel
 */

#include "utilesTest.h"

using namespace Test;

utilesTest::utilesTest() {}

utilesTest::~utilesTest() {}

void utilesTest::testSplitCorrectamente()
{
	std::vector<std::string> campos = Utiles::Metodos::split("hola/como/estas", '/');

	EXPECT_STREQ( "hola", campos[0].c_str() );
	EXPECT_STREQ( "como", campos[1].c_str() );
	EXPECT_STREQ( "estas", campos[2].c_str() );
}

void utilesTest::testCodearYEncodearBase64Correctamente()
{
	std::string original("bytesAEncondear\n\b\r¶€ð");

	std::string codeado = base64_encode((unsigned char*)original.data(), 25);

	std::string decodeado = base64_decode( codeado.c_str() );

	EXPECT_STREQ( original.c_str(), decodeado.c_str() );
}
void utilesTest::testCrearLogsCorrectamente()
{
	std::string nombreClase = "utilesTest";

	Utiles::Log::instancia()->info("informacionTest", nombreClase );
	Utiles::Log::instancia()->warn("warningTest", nombreClase );
	Utiles::Log::instancia()->error("errorTest", nombreClase );
	Utiles::Log::instancia()->debug("debugTest", nombreClase );
	Utiles::Log::instancia()->trace("traceTest", nombreClase );

	ConexionServidor::BaseDeDatos::ManagerArchivos manager;
	EXPECT_EQ(true, manager.existe( "info.log" ) );
	EXPECT_EQ(true, manager.existe( "warn.log" ) );
	EXPECT_EQ(true, manager.existe( "error.log" ) );
	EXPECT_EQ(true, manager.existe( "debug.log" ) );
	EXPECT_EQ(true, manager.existe( "trace.log" ) );

//	Utiles::Log* log = new Utiles::Log();
//	delete log;
	//Utiles::Log log;
}
void utilesTest::testLectorLeeParametrosCorrectamente()
{
	char l[] = "-l";
	char nivel[] = "nivel";
	char p[] = "-p";
	char puerto[] = "8080";
	char ayuda[] = "-h";

	char *parametros[] = { l, nivel, p, puerto, ayuda };

	ConexionServidor::LectorParametros lector;

	lector.leerParametros(5, parametros );

	EXPECT_STREQ( "nivel", lector.getNivelLog().c_str() );
	EXPECT_STREQ( "8080", lector.getPuerto().c_str() );
	EXPECT_EQ( 8080, lector.getPuertoInt() );
	EXPECT_EQ( true, lector.getAyuda() );

}
