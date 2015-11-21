/*
 * OperacionCompartirArchivo.h
 *
 *  Created on: 30/10/2015
 *      Author: manuel
 */

#ifndef OPERACIONCOMPARTIRARCHIVO_H_
#define OPERACIONCOMPARTIRARCHIVO_H_

// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"
// entidades
#include "../bd/entidades/User.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"
#include "../bd/entidades/ArchivoCompartirConUsuarios.h"
// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionCompartirArchivo: public IOperable
{
public:

	OperacionCompartirArchivo();
	virtual ~OperacionCompartirArchivo();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

	void compartirArchivoConUsuario(std::string mail, std::string carpeta );

	std::string nombreClase();
};
};
};

#endif /* OPERACIONCOMPARTIRARCHIVO_H_ */
