/*
 * OperacionCompartirCarpeta.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONCOMPARTIRCARPETA_H_
#define OPERACIONCOMPARTIRCARPETA_H_

// conexion
#include "../conexion/Respuesta.h"
// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"
// entidades
#include "../bd/entidades/User.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"
#include "../bd/entidades/CarpetaCompartirConUsuarios.h"
// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionCompartirCarpeta: public IOperable
{
public:
	OperacionCompartirCarpeta();
	virtual ~OperacionCompartirCarpeta();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

	void compartirCarpetaConUsuario(std::string mail, std::string carpeta );

};
};
};

#endif /* OPERACIONCOMPARTIRCARPETA_H_ */
