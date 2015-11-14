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

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido);

	void imprimir();

};
};
};

#endif /* OPERACIONCOMPARTIRCARPETA_H_ */
