/*
 * OperacionPrincipal.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONPRINCIPAL_H_
#define OPERACIONPRINCIPAL_H_

// Operaciones
#include "IOperable.h"
// entidades
#include "../bd/entidades/User.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionPrincipal: public IOperable {

public:
	OperacionPrincipal();
	virtual ~OperacionPrincipal();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido);

	virtual void imprimir();
};
};
};

#endif /* OPERACIONPRINCIPAL_H_ */
