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

	ConexionServidor::Respuesta delet(std::string contenido);
	ConexionServidor::Respuesta get(std::string contenido);
	ConexionServidor::Respuesta post(std::string contenido);
	ConexionServidor::Respuesta put(std::string contenido);

	void imprimir();

};
};
};

#endif /* OPERACIONCOMPARTIRCARPETA_H_ */
