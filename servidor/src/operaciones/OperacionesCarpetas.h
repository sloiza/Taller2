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

	void delet(std::string contenido);
	void get(std::string contenido);
	void post(std::string contenido);
	void put(std::string contenido);

	std::string impresion();

};
};
};

#endif /* OPERACIONESCARPETAS_H_ */
