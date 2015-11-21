/*
 * OperacionesPapelera.h
 *
 *  Created on: 16/11/2015
 *      Author: manuel
 */

#ifndef OPERACIONESPAPELERA_H_
#define OPERACIONESPAPELERA_H_

// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"
// entidadaes
#include "../bd/entidades/ContenidoPorCarpeta.h"
#include "../bd/entidades/User.h"
#include "../bd/entidades/ArchivoLogico.h"
#include "../bd/entidades/CarpetaLogica.h"
// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class OperacionesPapelera : public IOperable
{
public:
	OperacionesPapelera();
	virtual ~OperacionesPapelera();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

	void restaurarCarpeta(Utiles::Bytes* contenido, std::string mailDeUsuario);

};
};
};

#endif /* OPERACIONESPAPELERA_H_ */
