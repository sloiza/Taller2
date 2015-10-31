/*
 * OperacionesCarpetas.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONESCARPETAS_H_
#define OPERACIONESCARPETAS_H_

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

	ConexionServidor::Respuesta delet(std::string contenido);
	ConexionServidor::Respuesta get(std::string contenido);
	ConexionServidor::Respuesta post(std::string contenido);
	ConexionServidor::Respuesta put(std::string contenido);

	void imprimir();

};
};
};

#endif /* OPERACIONESCARPETAS_H_ */
