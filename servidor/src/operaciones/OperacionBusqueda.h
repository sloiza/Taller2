/*
 * OperacionBusqueda.h
 *
 *  Created on: 17/11/2015
 *      Author: manuel
 */

#ifndef OPERACIONBUSQUEDA_H_
#define OPERACIONBUSQUEDA_H_

// conexion
#include "../conexion/Respuesta.h"
// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"
// entidades
#include "../bd/entidades/ContenidoPorCarpeta.h"
#include "../bd/entidades/ArchivoLogico.h"
#include "../bd/entidades/User.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionBusqueda : public IOperable
{
public:

	typedef ConexionServidor::BaseDeDatos::ArchivoLogico tipoArchivoLog;
	typedef ConexionServidor::BaseDeDatos::ArchivoLogico::enumEtiquetas enumEtiquetas;

	OperacionBusqueda();
	virtual ~OperacionBusqueda();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

};

#endif /* OPERACIONBUSQUEDA_H_ */
