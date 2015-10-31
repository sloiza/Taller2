/*
 * IMetodoREST.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef IMETODOREST_H_
#define IMETODOREST_H_

// conexion
#include "../../conexion/Respuesta.h"
// Base de datos
#include "../../operaciones/IOperable.h"
#include "../../bd/JsonInfo.h"

namespace ConexionServidor
{

namespace Request
{

class IMetodoREST {
public:
	IMetodoREST() {}
	virtual ~IMetodoREST() {}

	virtual ConexionServidor::Respuesta ejecutar(ConexionServidor::Operaciones::IOperable* operacion, std::string contenido) = 0;
	virtual std::string impresion() = 0;
};
};
};

#endif /* IMETODOREST_H_ */
