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

	void delet(std::string contenido);
	void get(std::string contenido);
	void post(std::string contenido);
	void put(std::string contenido);

	std::string impresion();
};
};
};

#endif /* OPERACIONPRINCIPAL_H_ */
