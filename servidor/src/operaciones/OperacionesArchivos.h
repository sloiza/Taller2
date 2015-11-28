/// \file OperacionesArchivos.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de archivos.
#ifndef OPERACIONESARCHIVOS_H_
#define OPERACIONESARCHIVOS_H_

// conexion
#include "../conexion/Respuesta.h"
// base de datos
#include "../archivos/Archivo.h"
// entidades
#include "../bd/entidades/ArchivoLogico.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"
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
/// \brief Clase que realiza las operaciones de archivos.
class OperacionesArchivos : public IOperable {

public:
	/// \brief Constructor.
	OperacionesArchivos();
	/// \brief Destructor.
	virtual ~OperacionesArchivos();

	/// \brief Ejecuta el metodo DELETE.
	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo GET.
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo POST.
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo PUT.
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	/// \brief Imprimir la operacion.
	void imprimir();

	static ConexionServidor::BaseDeDatos::Archivo* archivoTemporal;
	static bool sobreescribir;

	/// \brief Agrega archivo al contenido de su carpeta.
	static void agregarArchivoALaListaDeArchivosPorCarpeta(std::string);
	/// \brief Agrega archivo a la lista de archivos del usuario.
	static void agregarArchivoALaListaDeArchivosDeUsuario(std::string);

};
};
};

#endif /* OPERACIONESARCHIVOS_H_ */
