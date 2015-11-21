/*
 * ContenidoPorCarpeta.h
 *
 *  Created on: 4/11/2015
 *      Author: manuel
 */

#ifndef CONTENIDOPORCARPETA_H_
#define CONTENIDOPORCARPETA_H_

// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class ContenidoPorCarpeta : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		NOMBRE,
		DIRECCION,
		ARCHIVOS,
		CARPETAS
	};
	static const std::string etiquetas[];

	ContenidoPorCarpeta();
	ContenidoPorCarpeta(std::string contenido);
	virtual ~ContenidoPorCarpeta();

	void setPath(std::string), setNombre(std::string), setDireccion(std::string), agregarArchivo(std::string), agregarCarpeta(std::string);
	void eliminarArchivo(std::string), eliminarCarpeta(std::string), eliminarTodosLosArchivos(), eliminarTodasLosCarpetas();

	std::string getPath(), getNombre(), getDireccion();
	std::vector<std::string> getArchivos(), getCarpetas();

	// Metodos de EntidadDB
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();

};
};
};

#endif /* CONTENIDOPORCARPETA_H_ */
