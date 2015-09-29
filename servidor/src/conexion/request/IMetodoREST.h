/*
 * IMetodoREST.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef IMETODOREST_H_
#define IMETODOREST_H_

namespace ConexionServidor
{

namespace Request
{

class IMetodoREST {
public:
	IMetodoREST(){}
	virtual ~IMetodoREST(){}

	virtual void ejecutar(std::string entidad, std::string contenido) = 0;
	virtual std::string impresion() = 0;
};
};
};

#endif /* IMETODOREST_H_ */
