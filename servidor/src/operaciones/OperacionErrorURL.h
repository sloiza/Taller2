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

	void delet(std::string contenido);
	void get(std::string contenido);
	void post(std::string contenido);
	void put(std::string contenido);

	std::string impresion();

};
};
};

#endif /* OPERACIONERRORURL_H_ */
