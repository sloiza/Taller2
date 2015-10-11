/*
 * JsonInfo.h
 *
 *  Created on: 10/10/2015
 *      Author: manuel
 */

#ifndef JSONINFO_H_
#define JSONINFO_H_

// Json
#include<json/json.h>

// Utiles
#include "../utiles/Log.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class JsonInfo {
public:
	JsonInfo();
	JsonInfo(std::string contenido);
	virtual ~JsonInfo();

	std::string getAtributo(std::string campo, std::string valorDefault);
	std::string getContenido();

private:
	Json::Value raiz;
	std::string contenido;

};
};
};

#endif /* JSONINFO_H_ */
