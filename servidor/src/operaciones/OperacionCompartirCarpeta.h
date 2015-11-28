/// \file OperacionCompartirCarpeta.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de compartir carpetas.
#ifndef OPERACIONCOMPARTIRCARPETA_H_
#define OPERACIONCOMPARTIRCARPETA_H_

// conexion
#include "../conexion/Respuesta.h"
// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"
#include "Acciones.h"
// entidades
#include "../bd/entidades/User.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"
#include "../bd/entidades/CarpetaCompartirConUsuarios.h"
// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Clase que realiza las operaciones de compartir carpetas.
class OperacionCompartirCarpeta: public IOperable
{
public:
	/// \brief Constructor.
	OperacionCompartirCarpeta();
	/// \brief Destructor.
	virtual ~OperacionCompartirCarpeta();

	/// \brief Ejecuta el metodo DELETE.
	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo GET.
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo POST.
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo PUT.
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	/// \brief Imprime operacion.
	void imprimir();

	/// \brief Agrega el archivo a la carpeta compartida del usuario.
	void compartirCarpetaConUsuario(std::string mail, std::string carpeta );

	/// \brief Devuelve nombre de la clase.
	std::string nombreClase();

private:

	ConexionServidor::Operaciones::Acciones acciones;

};
};
};

#endif /* OPERACIONCOMPARTIRCARPETA_H_ */
