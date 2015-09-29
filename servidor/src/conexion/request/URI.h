/*
 * URI.h
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#ifndef URI_H_
#define URI_H_

// STL
#include <string>

namespace ConexionServidor
{
namespace Request
{

class URI {
public:
	URI();
	URI(std::string);
	virtual ~URI();

	std::string getURI();

	std::string getEntidadAManejar();

private:
	std::string uri;
};

};
};

#endif /* URI_H_ */
