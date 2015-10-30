/*
 * CreadorDeOperaciones.h
 *
 *  Created on: 29/10/2015
 *      Author: manuel
 */

#ifndef CREADORDEOPERACIONES_H_
#define CREADORDEOPERACIONES_H_


// request
#include "../conexion/request/URI.h"
// operaciones
#include "OperacionesArchivos.h"
#include "OperacionesUsuario.h"
#include "OperacionErrorURL.h"

// STL
#include <iostream>
#include <vector>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

struct Recurso
{
	std::string nombre;
	std::vector<Recurso*> hijos;
	IOperable* operacion;
};

class CreadorDeOperaciones
{
public:
	CreadorDeOperaciones();
	virtual ~CreadorDeOperaciones();

	static void crearArbolDeRecursos();
	static void liberarArbolDeRecursos();

	static void dividirRecursos(std::string uri);
	static IOperable* getOperacion(ConexionServidor::Request::URI* uri);
	static IOperable* reconocerUriRecursivamente(Recurso* recurso, int nivelArbol);
	static void liberarRecusivamente(Recurso* recurso);

	static std::vector<std::string> getCampos();

private:
	static std::vector<std::string> campos;
	static Recurso* raiz;
};
};
};

#endif /* CREADORDEOPERACIONES_H_ */
