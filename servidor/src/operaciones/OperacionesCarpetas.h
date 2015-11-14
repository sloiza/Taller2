/*
 * OperacionesCarpetas.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONESCARPETAS_H_
#define OPERACIONESCARPETAS_H_


// carpetas
#include "../archivos/Carpeta.h"

// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionesCarpetas: public IOperable {
public:
	OperacionesCarpetas();
	virtual ~OperacionesCarpetas();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

};
};
};

#endif /* OPERACIONESCARPETAS_H_ */
