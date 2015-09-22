/*
 * LectorParametros.h
 *
 *  Created on: 19/9/2015
 *      Author: manuel
 */

#ifndef LECTORPARAMETROS_H_
#define LECTORPARAMETROS_H_

// STL
#include <iostream>
#include <map>
#include <string>

// Conexion servidor
#include "utiles.h"

namespace ConexionServidor
{

class LectorParametros
{
	public:
		static const char* PARAM_LOG;
		static const char* PARAM_PUERTO;
		static const char* PARAM_AYUDA;

		LectorParametros();
		virtual ~LectorParametros();

		void leerParametros(int cantidadArgumentos, char** argumentos);

		const std::string getNivelLog();
		const std::string getPuerto();
		const int getPuertoInt();
		const bool getAyuda();

		void imprimir();

	private:
		std::map<std::string, std::string> parametros;
};

} /* namespace ConexionServidor */

#endif /* LECTORPARAMETROS_H_ */
