/// \file OperacionCompartirArchivo.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de compartir archivos.
#ifndef OPERACIONCOMPARTIRARCHIVO_H_
#define OPERACIONCOMPARTIRARCHIVO_H_

// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"
#include "Acciones.h"
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
/// \brief Clase que realiza las operaciones de compartir archivos.
class OperacionCompartirArchivo: public IOperable
{
public:
	/// \brief Constructor.
	OperacionCompartirArchivo();
	/// \brief Destructor.
	virtual ~OperacionCompartirArchivo();

	/// \brief Ejecuta el metodo DELETE.
	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo GET.
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo POST.
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo PUT.
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	/// \brief Imprime la operacion.
	void imprimir();

	/// \brief Agrega el archivo a la carpeta compartida del usuario.
	bool compartirArchivoConUsuario(std::string mail, std::string carpeta );

	/// \brief Devuelve nombre de la clase.
	std::string nombreClase();
};
};
};

#endif /* OPERACIONCOMPARTIRARCHIVO_H_ */
