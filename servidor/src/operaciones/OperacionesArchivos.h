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

	ConexionServidor::Respuesta delet(std::string contenido);
	ConexionServidor::Respuesta get(std::string contenido);
	ConexionServidor::Respuesta post(std::string contenido);
	ConexionServidor::Respuesta put(std::string contenido);

	void imprimir();
};
};
};

#endif /* OPERACIONESARCHIVOS_H_ */
