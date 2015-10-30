/*
 * OperacionCompartirArchivo.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONCOMPARTIRARCHIVO_H_
#define OPERACIONCOMPARTIRARCHIVO_H_

// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionCompartirArchivo: public IOperable
{
public:
	OperacionCompartirArchivo();
	virtual ~OperacionCompartirArchivo();

	void delet(std::string contenido);
	void get(std::string contenido);
	void post(std::string contenido);
	void put(std::string contenido);

	std::string impresion();

};
};
};

#endif /* OPERACIONCOMPARTIRARCHIVO_H_ */
