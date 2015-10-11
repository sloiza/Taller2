/*
 * LectorParametros.cpp
 *
 *  Created on: 19/9/2015
 *      Author: manuel
 */

#include "LectorParametros.h"

using namespace ConexionServidor;

const char* LectorParametros::PARAM_LOG = "-l";
const char* LectorParametros::PARAM_PUERTO = "-p";
const char* LectorParametros::PARAM_AYUDA = "-h";

enum IDS
{
	ID_PARAM_LOG,
	ID_PARAM_PUERTO,
	ID_PARAM_AYUDA
};

LectorParametros::LectorParametros() {}

LectorParametros::~LectorParametros() {}

void LectorParametros::leerParametros(int cantidadArgumentos, char** argumentos)
{
	// map para poder hacer un 'switch' con strings
	std::map<std::string, int> ids =
			{
					{ std::string(PARAM_LOG), ID_PARAM_LOG },
					{ std::string(PARAM_PUERTO), ID_PARAM_PUERTO },
					{ std::string(PARAM_AYUDA), ID_PARAM_AYUDA},
			};

	for( int i = 1; i < cantidadArgumentos; i++ )
	{
		std::string argumento(argumentos[i]);

		switch( ids[argumento] )
		{
			case ID_PARAM_LOG:
				{
					i++;
					std::string valor(argumentos[i]);
					parametros.insert( std::pair<std::string, std::string>(PARAM_LOG, valor));
					break;
				}
			case ID_PARAM_PUERTO:
				{
					i++;
					std::string valor(argumentos[i]);
					parametros.insert( std::pair<std::string, std::string>(PARAM_PUERTO, valor));
					break;
				}
			case ID_PARAM_AYUDA:
				{
					parametros.insert( std::pair<std::string, std::string>(PARAM_AYUDA, "ayuda"));
					return;
				}
			default: std::cout << "PARAMETRO NO RECONOCIDO.\n";
		}
	}
}

const std::string LectorParametros::getNivelLog()
{
	return parametros[PARAM_LOG];
}

const std::string LectorParametros::getPuerto()
{
	return parametros[PARAM_PUERTO];
}

const int LectorParametros::getPuertoInt()
{
	return Utiles::Metodos::toInt( parametros[PARAM_PUERTO] );
}

const bool LectorParametros::getAyuda()
{
	return parametros.find(PARAM_AYUDA) != parametros.end();
}

void LectorParametros::imprimir()
{
	for(std::map<std::string, std::string>::iterator it = parametros.begin(); it != parametros.end(); it++)
	{
		std::cout << "parametro: " << it->first.c_str() << " valor: " << it->second.c_str() << "\n";
	}
}
