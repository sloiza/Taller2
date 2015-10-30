/*
 * OperacionCompartirCarpeta.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONCOMPARTIRCARPETA_H_
#define OPERACIONCOMPARTIRCARPETA_H_

// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionCompartirCarpeta: public IOperable
{
public:
	OperacionCompartirCarpeta();
	virtual ~OperacionCompartirCarpeta();

	void delet(std::string contenido);
	void get(std::string contenido);
	void post(std::string contenido);
	void put(std::string contenido);

	std::string impresion();

};
};
};

#endif /* OPERACIONCOMPARTIRCARPETA_H_ */
