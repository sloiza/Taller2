/*
 * Archivo.h
 *
 *  Created on: 25/10/2015
 *      Author: manuel
 */

#ifndef ARCHIVOLOGICO_H_
#define ARCHIVOLOGICO_H_

// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class ArchivoLogico: public EntidadDB
{

public:

	enum enumEtiquetas
	{
		NOMBRE,
		EXTENSION,
		ETIQUETA,
		FECHA_ULTIMA_MODI,
		USUARIO_ULTIMA_MODI,
		PROPIETARIO,
		BAJA_LOGICA,
		DIRECCION,
	};

	static const std::string etiquetas[];

	ArchivoLogico();
	ArchivoLogico(std::string contenido);
	virtual ~ArchivoLogico();

	void setNombre(std::string), setExtension(std::string), setEtiqueta(std::string), setUltimaFechaModif(std::string),
			setUltimoUsuarioModif(std::string), setPropietario(std::string), setBajaLogica(std::string), setDireccion(std::string);

	std::string getNombre(), getExtension(), getEtiqueta(), getUltimaFechaModif(),
			getUltimoUsuarioModif(), getPropietario(), getBajaLogica(), getDireccion(), getNombreYExtension();

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

#endif /* ARCHIVOLOGICO_H_ */
