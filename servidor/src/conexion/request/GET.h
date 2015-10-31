/*
 * GET.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef GET_H_
#define GET_H_

// STL
#include <string>

// Request
#include "IMetodoREST.h"

namespace ConexionServidor
{
namespace Request
{

class GET : public IMetodoREST
{
public:
	GET();
	virtual ~GET();

	virtual ConexionServidor::Respuesta ejecutar(ConexionServidor::Operaciones::IOperable* entidad, std::string contenido);

	virtual std::string impresion();
};

};
};

#endif /* GET_H_ */
