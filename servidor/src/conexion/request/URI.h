/*
 * URI.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef URI_H_
#define URI_H_

// STL
#include <iostream>
#include <string>
#include <vector>

// Base de datos
#include "../../bd/entidades/EntidadBD.h"

namespace ConexionServidor
{
namespace Request
{

class URI {
public:
	URI();
	URI(std::string);
	virtual ~URI();

	//std::string getURI();
	std::string getURI();

	//std::string getEntidadAManejar();
	ConexionServidor::BaseDeDatos::EntidadDB* getEntidadAManejar();

	std::vector<std::string> getRecursosDividos();

private:
	std::string uri;
};

};
};

#endif /* URI_H_ */
