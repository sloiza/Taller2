/*
 * CarpetaCompartirConUsuarios.h
 *
 *  Created on: 14/11/2015
 *      Author: manuel
 */

#ifndef CARPETACOMPARTIRCONUSUARIOS_H_
#define CARPETACOMPARTIRCONUSUARIOS_H_

// utiles
#include "../../utiles/utiles.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"
// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class CarpetaCompartirConUsuarios : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		NOMBRE,
		DIRECCION,
		USUARIOS
	};
	static const std::string etiquetas[];

	CarpetaCompartirConUsuarios();
	CarpetaCompartirConUsuarios(std::string);
	virtual ~CarpetaCompartirConUsuarios();

	std::string getNombreCarpeta(), getDireccionCarpeta(), getPathCarpeta();
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

#endif /* CARPETACOMPARTIRCONUSUARIOS_H_ */
