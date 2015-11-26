/// \file OperacionBusqueda.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de busqueda.
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
// utiles
#include "../utiles/Log.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Clase que realiza las operaciones de busqueda.
class OperacionBusqueda : public IOperable
{
public:

	typedef ConexionServidor::BaseDeDatos::ArchivoLogico tipoArchivoLog;
	typedef ConexionServidor::BaseDeDatos::ArchivoLogico::enumEtiquetas enumEtiquetas;

	/// \brief Constructor.
	OperacionBusqueda();
	/// \brief Destructor.
	virtual ~OperacionBusqueda();

	/// \brief Ejecuta el metodo DELETE.
	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo GET.
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo POST.
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo PUT.
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

	/// \brief Devuelve el set de archivos de busqueda.
	std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> getArchivosAFiltrar(std::vector<std::string> pathsAFiltrar);

	/// \brief Filtra archivos por nombre.
	std::vector<std::string> buscarArchivosPorNombre(std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivosAFiltrar, std::string query);
	/// \brief Filtra archivos por extension.
	std::vector<std::string> buscarArchivosPorExtension(std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivosAFiltrar, std::string query);
	/// \brief Filtra archivos por etiqueta.
	std::vector<std::string> buscarArchivosPorEtiqueta(std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivosAFiltrar, std::string query);
	/// \brief Filtra archivos por propietario	/// \brief Filtra archivos por nombre..
	std::vector<std::string> buscarArchivosPorPropietario(std::vector<ConexionServidor::BaseDeDatos::ArchivoLogico*> archivosAFiltrar, std::string query);

	/// \brief Devuelve el nombre de la clase.
	std::string nombreClase();
};
};
};

#endif /* OPERACIONBUSQUEDA_H_ */
