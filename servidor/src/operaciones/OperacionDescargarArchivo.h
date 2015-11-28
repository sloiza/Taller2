/// \file OperacionDescargarArchivo.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de descargar archivo.
#ifndef OPERACIONDESCARGARARCHIVO_H_
#define OPERACIONDESCARGARARCHIVO_H_

// archivos
#include "../archivos/Archivo.h"
// conexion
#include "../conexion/Respuesta.h"
// Operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Clase que realiza las operaciones de descargar archivo.
class OperacionDescargarArchivo: public IOperable
{
public:
	/// \brief Constructor.
	OperacionDescargarArchivo();
	/// \brief Destructor.
	virtual ~OperacionDescargarArchivo();

	/// \brief Ejecuta el metodo DELETE.
	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo GET.
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo POST.
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo PUT.
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	/// \brief Imprimir operacion.
	void imprimir();
};
};
};

#endif /* OPERACIONDESCARGARARCHIVO_H_ */
