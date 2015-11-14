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

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido);

	void imprimir();

};
};
};

#endif /* OPERACIONCOMPARTIRARCHIVO_H_ */
