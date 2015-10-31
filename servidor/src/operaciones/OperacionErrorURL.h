/*
 * OperacionErrorURL.h
 *
 *  Created on: 29/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONERRORURL_H_
#define OPERACIONERRORURL_H_

// operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionErrorURL: public IOperable {
public:
	OperacionErrorURL();
	virtual ~OperacionErrorURL();

	ConexionServidor::Respuesta delet(std::string contenido);
	ConexionServidor::Respuesta get(std::string contenido);
	ConexionServidor::Respuesta post(std::string contenido);
	ConexionServidor::Respuesta put(std::string contenido);

	void imprimir();

};
};
};

#endif /* OPERACIONERRORURL_H_ */
