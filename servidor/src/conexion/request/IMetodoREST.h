/*
 * IMetodoREST.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef IMETODOREST_H_
#define IMETODOREST_H_

// Base de datos
#include "../../bd/entidades/EntidadBD.h"
#include "../../bd/JsonInfo.h"

namespace ConexionServidor
{

namespace Request
{

class IMetodoREST {
public:
	IMetodoREST() {}
	virtual ~IMetodoREST() {}

	virtual void ejecutar(ConexionServidor::BaseDeDatos::EntidadDB* entidad, std::string contenido) = 0;
	virtual std::string impresion() = 0;
};
};
};

#endif /* IMETODOREST_H_ */
