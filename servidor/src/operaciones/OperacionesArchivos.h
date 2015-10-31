/*
 * OperacionesArchivos.h
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONESARCHIVOS_H_
#define OPERACIONESARCHIVOS_H_

// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionesArchivos : public IOperable {

public:
	OperacionesArchivos();
	virtual ~OperacionesArchivos();

	void delet(std::string contenido);
	void get(std::string contenido);
	void post(std::string contenido);
	void put(std::string contenido);

	std::string impresion();
};
};
};

#endif /* OPERACIONESARCHIVOS_H_ */
