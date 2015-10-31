/*
 * OperacionDescargarArchivo.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONDESCARGARARCHIVO_H_
#define OPERACIONDESCARGARARCHIVO_H_

// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionDescargarArchivo: public IOperable
{
public:
	OperacionDescargarArchivo();
	virtual ~OperacionDescargarArchivo();

	void delet(std::string contenido);
	void get(std::string contenido);
	void post(std::string contenido);
	void put(std::string contenido);

	std::string impresion();
};
};
};

#endif /* OPERACIONDESCARGARARCHIVO_H_ */
