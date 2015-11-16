/*
 * ArchivoCompartirConUsuarios.h
 *
 *  Created on: 16/11/2015
 *      Author: manuel
 */

#ifndef ARCHIVOCOMPARTIRCONUSUARIOS_H_
#define ARCHIVOCOMPARTIRCONUSUARIOS_H_

// utiles
#include "../../utiles/utiles.h"
// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class ArchivoCompartirConUsuarios : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		NOMBRE,
		DIRECCION,
		EXTENSION,
		USUARIOS
	};
	static const std::string etiquetas[];

	ArchivoCompartirConUsuarios();
	ArchivoCompartirConUsuarios(std::string);
	virtual ~ArchivoCompartirConUsuarios();

	std::string getNombreArchivo(), getDireccionArchivo(), getPathArchivo(), getExtensionArchivo();
	std::vector<std::string> getUsuariosACompartirles();

	// Metodos de EntidadDB
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();
};
};
};

#endif /* ARCHIVOCOMPARTIRCONUSUARIOS_H_ */
