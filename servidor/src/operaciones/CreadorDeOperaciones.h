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
#include "OperacionBusqueda.h"
#include "OperacionCompartirArchivo.h"
#include "OperacionCompartirCarpeta.h"
#include "OperacionDescargarArchivo.h"
#include "OperacionesArchivos.h"
#include "OperacionesUsuario.h"
#include "OperacionesCarpetas.h"
#include "OperacionErrorURL.h"
#include "OperacionPrincipal.h"
#include "OperacionesPapelera.h"
#include "InfoOperaciones.h"
// utiles
#include "../utiles/Log.h"

// STL
#include <iostream>
#include <vector>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class CreadorDeOperaciones
{
public:
	enum OPERACIONES
	{
		PRINCIPAL,
		USUARIOS,
		ARCHIVOS,
		CARPETAS,
		COMPARTIR_ARCHIVO,
		COMPARTIR_CARPETA,
		DESCARGAR,
		PAPELERA,
		BUSCAR
	};

	struct Recurso
	{
		std::string nombre;
		std::vector<Recurso*> hijos;
		IOperable* operacion;
		InfoOperaciones::OPERACIONES tipo;
	};

	CreadorDeOperaciones();
	virtual ~CreadorDeOperaciones();

	static void crearArbolDeRecursos();
	static void liberarArbolDeRecursos();

	static IOperable* getOperacion(ConexionServidor::Request::URI* uri);
	static IOperable* reconocerUriRecursivamente(Recurso* recurso, int nivelArbol);
	static void liberarRecusivamente(Recurso* recurso);

	static std::vector<std::string> getCampos();

	static IOperable* crearOperacion(InfoOperaciones::OPERACIONES tipo);

	static std::string nombreClase();

private:
	static std::vector<std::string> campos;
	static Recurso* raiz;
};
};
};

#endif /* CREADORDEOPERACIONES_H_ */
