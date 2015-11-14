/*
 * Respuesta.h
 *
 *  Created on: 31/10/2015
 *      Author: manuel
 */

#ifndef RESPUESTA_H_
#define RESPUESTA_H_

// entidad
#include "../bd/entidades/EntidadBD.h"

// STL
#include <string>

namespace ConexionServidor
{

class Respuesta : public BaseDeDatos::EntidadDB
{
public:

	enum enumEtiquetas
	{
		ESTADO,
		MENSAJE
	};

	static const std::string etiquetas[];

	Respuesta();
	virtual ~Respuesta();

	std::string getEstado();
	std::string getMensaje();

	void setEstado(std::string estado);
	void setMensaje(std::string mensaje);

	// Metodos de EntidadDB
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();
};
};

#endif /* RESPUESTA_H_ */
