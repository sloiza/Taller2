/// \file JsonInfo.h
/// \date 2015-11-26
/// \brief Clase wrapper de json.
#ifndef JSONINFO_H_
#define JSONINFO_H_

// Json
//#include <json/json.h>
//#include "../json/json.h"
#include "json/json.h"

// Utiles
#include "../utiles/Log.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
/// \brief Clase wrapper de json.
class JsonInfo {
public:
	/**
	 * @brief Constructor: Crea objeto con formato json
	 */
	JsonInfo();
	JsonInfo(std::string contenido);
	virtual ~JsonInfo();
	/**
	 * @brief Devuelve el valor del campo seleccionado.
	 */
	std::string getAtributo(std::string campo, std::string valorDefault);
	/**
	 * @brief Agrega el campo y valor nuevos al json.
	 */
	void setAtributo(std::string campo, std::string valorNuevo);
	/**
	 * @brief Agrega el Valor a un campo específico.
	 */
	void agregarValorAAtributo(std::string campo, std::string valorAAgregar);
	/**
	 * @brief Agrega un valor específico de un determinado campo.
	 */
	void borrarValorDeAtributo(std::string campo, std::string valorABorrar);
	/**
	 * @brief Elimina los valores de un campo específico
	 */
	void borrarValoresDeAtributo(std::string campo);
	/**
	 * @brief Obtener todos los valores de un campo
	 */
	std::vector<std::string> getListaDeValorDeAtributo(std::string campo, std::string valorDefault);
	void setContenido();
	/**
	 * @brief Obtiene el json contenido
	 */
	std::string getContenido();
	/**
	 * @brief Parsea el contenido en el Json
	 */
	void setContenido(std::string contenido);
	  
	/**
	 * @brief Elimina el contenido de la raiz
	 */
	void limpiar();
	/**
	 * @brief Indica si el json parseado es correcto
	 */
	bool estadoOk();
	/**
	 * @brief Imprime el contenido del json
	 */
	void imprimir();

private:
	Json::Value raiz;
	std::string contenido;
	bool error;

};
};
};

#endif /* JSONINFO_H_ */
