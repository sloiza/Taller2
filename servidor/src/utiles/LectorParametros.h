/// \file LectorParametros.h
/// \date 2015-11-26
/// \brief Clase que lee los parametros de entrada.
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
/// \brief Clase que lee los parametros de entrada.
class LectorParametros
{
	public:
		static const char* PARAM_LOG;
		static const char* PARAM_PUERTO;
		static const char* PARAM_AYUDA;

		/// \brief Constructor.
		LectorParametros();
		/// \brief Destructor.
		virtual ~LectorParametros();

		/// \brief Lee y guarda los parametros de entrada.
		void leerParametros(int cantidadArgumentos, char** argumentos);

		/// \brief Devuelve el nivel de log.
		const std::string getNivelLog();
		/// \brief Devuelve el puerto como 'string'.
		const std::string getPuerto();
		/// \brief Deuelvo el puerto como 'int'.
		const int getPuertoInt();
		/// \brief Chequea si se solicito ayuda.
		const bool getAyuda();

		/// \brief Imprime el lector de parametros.
		void imprimir();

	private:
		std::map<std::string, std::string> parametros;
};

};

#endif /* LECTORPARAMETROS_H_ */
