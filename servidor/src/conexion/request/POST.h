/*
 * POST.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef POST_H_
#define POST_H_

// STL
#include <string>

// Request
#include "IMetodoREST.h"

namespace ConexionServidor
{
namespace Request
{

class POST : public IMetodoREST
{
public:
	POST();
	virtual ~POST();

	virtual void ejecutar(ConexionServidor::BaseDeDatos::EntidadDB* entidad, std::string contenido);

	virtual std::string impresion();
};

};
};

#endif /* POST_H_ */
