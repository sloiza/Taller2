/*
 * OperacionesUsuario.h
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONESUSUARIO_H_
#define OPERACIONESUSUARIO_H_

// conexion
#include "../conexion/Respuesta.h"
// entidades
#include "../bd/entidades/User.h"
// carpetas
#include "../archivos/Carpeta.h"
// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionesUsuario : public IOperable {

public:
	OperacionesUsuario();
	virtual ~OperacionesUsuario();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido);

	void imprimir();

private:
	bool existeUsuarioConLosMismosDatos(std::string);
	bool passwordValido(std::string);
};
};
};

#endif /* OPERACIONESUSUARIO_H_ */
