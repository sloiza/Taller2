/*
 * DELETE.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef DELETE_H_
#define DELETE_H_

// STL
#include <string>

// Request
#include "IMetodoREST.h"

namespace ConexionServidor
{
namespace Request
{

class DELETE : public IMetodoREST
{
public:
	DELETE();
	virtual ~DELETE();

	virtual void ejecutar(std::string entidad, std::string contenido);

	virtual std::string impresion();
};

};
};

#endif /* DELETE_H_ */
