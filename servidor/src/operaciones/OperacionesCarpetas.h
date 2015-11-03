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

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido);

	void imprimir();

};
};
};

#endif /* OPERACIONESCARPETAS_H_ */
