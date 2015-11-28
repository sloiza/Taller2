/*
 * Log.cpp
 *
 *  Created on: 28/9/2015
 *      Author: manuel
 */

#include "Log.h"

using namespace Utiles;

Log* Log::ptr = NULL;
std::fstream Log::logInfo;
std::fstream Log::logError;
std::fstream Log::logWarn;
std::fstream Log::logDebug;
std::fstream Log::logTrace;

Log::Log(){}

Log::~Log()
{
	this->destruir();
}

void Log::destruir ()
{
	if( logInfo.is_open() )
	{
		logInfo.close();
	}
	if( logError.is_open() )
	{
		logError.close();
	}
	if( logDebug.is_open() )
	{
		logDebug.close();
	}
	if( logTrace.is_open() )
	{
		logTrace.close();
	}

	if ( ptr != NULL ) {
		delete ( ptr );
		ptr = NULL;
	}
}

Log* Log::instancia()
{
	if( ptr == NULL )
		ptr = new Log();
	return ptr;
}

void Log::info(const std::string& mensaje, const std::string& autor)
{
	logInfo.open("info.log", std::fstream::out | std::fstream::app);

	std::string mensaje_completo =
			Utiles::Metodos::fechaYhora() +" "+ autor +": " + mensaje + "\n";

	logInfo.write(mensaje_completo.c_str(), mensaje_completo.size());

	logInfo.close();

	if( logInfo.good() == false ){
		std::string error = "Error al escribir en el log.";
		perror(error.c_str());
	}
}

void Log::debug(const std::string& mensaje, const std::string& autor)
{
	logDebug.open("debug.log", std::fstream::out | std::fstream::app);

	std::string mensaje_completo =
			Utiles::Metodos::fechaYhora() +" "+ autor +": " + mensaje + "\n";

	logDebug.write(mensaje_completo.c_str(), mensaje_completo.size());

	logDebug.close();

	if( logDebug.good() == false ){
		std::string error = "Error al escribir en el log.";
		perror(error.c_str());
	}
}

void Log::error(const std::string& mensaje, const std::string& autor)
{
	logError.open("error.log", std::fstream::out | std::fstream::app);

	std::string mensaje_completo =
			Utiles::Metodos::fechaYhora() +" "+ autor +": " + mensaje + "\n";

	logError.write(mensaje_completo.c_str(), mensaje_completo.size());

	logError.close();

	if( logError.good() == false ){
		std::string error = "Error al escribir en el log.";
		perror(error.c_str());
	}
}

void Log::warn(const std::string& mensaje, const std::string& autor)
{
	logWarn.open("warn.log", std::fstream::out | std::fstream::app);

	std::string mensaje_completo =
			Utiles::Metodos::fechaYhora() +" "+ autor +": " + mensaje + "\n";

	logWarn.write(mensaje_completo.c_str(), mensaje_completo.size());

	logWarn.close();

	if( logWarn.good() == false ){
		std::string error = "Error al escribir en el log.";
		perror(error.c_str());
	}
}
void Log::trace(const std::string& mensaje, const std::string& autor)
{
	logTrace.open("trace.log", std::fstream::out | std::fstream::app);

	std::string mensaje_completo =
			Utiles::Metodos::fechaYhora() +" "+ autor +": " + mensaje + "\n";

	logTrace.write(mensaje_completo.c_str(), mensaje_completo.size());

	logTrace.close();

	if( logTrace.good() == false ){
		std::string error = "Error al escribir en el log.";
		perror(error.c_str());
	}
}

