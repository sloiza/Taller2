/// \file CreadorDeOperaciones.h
/// \date 2015-11-26
/// \brief Clase que crea el mapa de recursos y sus operaciones.
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
/// \brief Clase que crea el mapa de recursos y sus operaciones.
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

	/// \brief Constructor.
	CreadorDeOperaciones();
	/// \brief Destructor.
	virtual ~CreadorDeOperaciones();

	/// \brief Crea arbol de recursos.
	static void crearArbolDeRecursos();
	/// \brief Libera arbol de recursos.
	static void liberarArbolDeRecursos();

	/// \brief Devuelve operacion segun la URI.
	static IOperable* getOperacion(ConexionServidor::Request::URI* uri);
	/// \brief Recorre el arbol de recursos.
	static IOperable* reconocerUriRecursivamente(Recurso* recurso, int nivelArbol);
	/// \brief Libera los recursos.
	static void liberarRecusivamente(Recurso* recurso);

	/// \brief Devuelve los campos de la uri.
	static std::vector<std::string> getCampos();

	/// \brief Crea la operacion segun el tipo.
	static IOperable* crearOperacion(InfoOperaciones::OPERACIONES tipo);

	/// \brief Devuelve el nombre de la clase.
	static std::string nombreClase();

private:
	static std::vector<std::string> campos;
	static Recurso* raiz;
};
};
};

#endif /* CREADORDEOPERACIONES_H_ */
