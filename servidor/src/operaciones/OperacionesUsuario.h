/*
 * OperacionesUsuario.h
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONESUSUARIO_H_
#define OPERACIONESUSUARIO_H_

// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionesUsuario : public IOperable {

public:
	OperacionesUsuario();
	virtual ~OperacionesUsuario();

	void delet(std::string contenido);
	void get(std::string contenido);
	void post(std::string contenido);
	void put(std::string contenido);

	std::string impresion();

};
};
};

#endif /* OPERACIONESUSUARIO_H_ */
