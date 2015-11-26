/// \file OperacionesCarpetas.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de carpetas.
#ifndef OPERACIONESCARPETAS_H_
#define OPERACIONESCARPETAS_H_


// carpetas
#include "../archivos/Carpeta.h"

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
/// \brief Clase que realiza las operaciones de carpetas.
class OperacionesCarpetas: public IOperable {
public:
	/// \brief Constructor.
	OperacionesCarpetas();
	/// \brief Destructor.
	virtual ~OperacionesCarpetas();

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

	/// \brief Agrega carpeta al contenido de su carpeta.
	void agregarCarpetaALaListaDeArchivosPorCarpeta(std::string contenido);
};
};
};

#endif /* OPERACIONESCARPETAS_H_ */
