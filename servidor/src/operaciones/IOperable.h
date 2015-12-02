/// \file IOperable.h
/// \date 2015-11-26
/// \brief Interfaz que implementan las operaciones de los metodos.
#ifndef IOPERABLE_H_
#define IOPERABLE_H_

// respuesta
#include "../conexion/Respuesta.h"

// utiles
#include "../utiles/Bytes.h"
// operaciones
#include "Acciones.h"

// STL
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Interfaz que implementan las operaciones de los metodos.
class IOperable
{
public:
	/// \brief Constructor.
	IOperable() {}
	/// \brief Destructor.
	virtual ~IOperable() {}

	/// \brief Ejecuta el metodo DELETE.
	virtual ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query) = 0;
	/// \brief Ejecuta el metodo GET.
	virtual ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query) = 0;
	/// \brief Ejecuta el metodo POST.
	virtual ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query) = 0;
	/// \brief Ejecuta el metodo PUT.
	virtual ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query) = 0;

	/// \brief Imprime la operacion.
	virtual void imprimir() = 0;

protected:

	Acciones acciones;
};
};
};



#endif /* IOPERABLE_H_ */
