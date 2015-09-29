/*
 * PUT.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef PUT_H_
#define PUT_H_

// STL
#include <string>

// Request
#include "IMetodoREST.h"

namespace ConexionServidor
{
namespace Request
{

class PUT : public IMetodoREST
{
public:
	PUT();
	virtual ~PUT();

	virtual void ejecutar(std::string entidad, std::string contenido);

	virtual std::string impresion();
};

};
};

#endif /* PUT_H_ */
