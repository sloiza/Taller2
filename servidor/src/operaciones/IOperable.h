/*
 * IOperable.h
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#ifndef IOPERABLE_H_
#define IOPERABLE_H_

// STL
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class IOperable {
public:
	IOperable() {}
	virtual ~IOperable() {}

	virtual void delet(std::string contenido) = 0;
	virtual void get(std::string contenido) = 0;
	virtual void post(std::string contenido) = 0;
	virtual void put(std::string contenido) = 0;

	virtual std::string impresion() = 0;
};
};
};



#endif /* IOPERABLE_H_ */
