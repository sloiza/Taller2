/*
 * JsonInfo.h
 *
 *  Created on: 10/10/2015
 *      Author: manuel
 */

#ifndef JSONINFO_H_
#define JSONINFO_H_

// Json
#include "json/json.h"

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
	void setAtributo(std::string campo, std::string valorNuevo);

	void agregarValorAAtributo(std::string campo, std::string valorAAgregar);
	void borrarValorDeAtributo(std::string campo, std::string valorABorrar);
	void borrarValoresDeAtributo(std::string campo);
	std::vector<std::string> getListaDeValorDeAtributo(std::string campo, std::string valorDefault);

	void setContenido();
	std::string getContenido();
	void setContenido(std::string contenido);
	void limpiar();

	bool estadoOk();
	void imprimir();

private:
	Json::Value raiz;
	std::string contenido;
	bool error;

};
};
};

#endif /* JSONINFO_H_ */
