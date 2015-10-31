/*
 * OperacionPrincipal.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONPRINCIPAL_H_
#define OPERACIONPRINCIPAL_H_

// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionPrincipal: public IOperable {

public:
	OperacionPrincipal();
	virtual ~OperacionPrincipal();

	ConexionServidor::Respuesta delet(std::string contenido);
	ConexionServidor::Respuesta get(std::string contenido);
	ConexionServidor::Respuesta post(std::string contenido);
	ConexionServidor::Respuesta put(std::string contenido);

	virtual void imprimir();
};
};
};

#endif /* OPERACIONPRINCIPAL_H_ */
