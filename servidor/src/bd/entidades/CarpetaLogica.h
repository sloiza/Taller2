/*
 * CarpetaLogica.h
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#ifndef CARPETALOGICA_H_
#define CARPETALOGICA_H_

// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class CarpetaLogica : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		NOMBRE,
		ETIQUETA,
		FECHA_ULTIMA_MODI,
		USUARIO_ULTIMA_MODI,
		PROPIETARIO,
		BAJA_LOGICA,
		DIRECCION,
	};
	static const std::string etiquetas[];

	CarpetaLogica();
	CarpetaLogica(std::string);
	virtual ~CarpetaLogica();

	void setNombre(std::string), setEtiqueta(std::string), setUltimaFechaModif(std::string),
			setUltimoUsuarioModif(std::string), setPropietario(std::string), setBajaLogica(std::string), setDireccion(std::string);

	std::string getNombre(), getEtiqueta(), getUltimaFechaModif(),
			getUltimoUsuarioModif(), getPropietario(), getBajaLogica(), getDireccion();

	std::string getPath();

	// Metodos de EntidadDB
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();
};
};
};

#endif /* CARPETALOGICA_H_ */
