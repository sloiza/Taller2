/*
 * Log.cpp
 *
 *  Created on: 28/9/2015
 *      Author: manuel
 */

#include "Log.h"

using namespace Utiles;

Log* Log::ptr = NULL;

Log::Log(){}

Log::~Log()
{
	if( log.is_open() )
	{
		log.close();
	}
}

void Log::destruir ()
{
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
	log.open("info.log", std::fstream::out | std::fstream::app);

	std::string mensaje_completo =
			Utiles::fechaYhora() +" "+ autor +": " + mensaje + "\n";

	log.write(mensaje_completo.c_str(), mensaje_completo.size());

	log.close();

	if( log.good() == false ){
		std::string error = "Error al escribir en el log.";
		perror(error.c_str());
	}
}
