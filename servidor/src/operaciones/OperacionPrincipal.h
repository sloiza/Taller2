/// \file OperacionPrincipal.h
/// \date 2015-11-26
/// \brief Clase que realiza la operacion principal.
#ifndef OPERACIONPRINCIPAL_H_
#define OPERACIONPRINCIPAL_H_

// Operaciones
#include "IOperable.h"
// entidades
#include "../bd/entidades/User.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Clase que realiza la operacion principal.
class OperacionPrincipal: public IOperable {

public:
	OperacionPrincipal();
	virtual ~OperacionPrincipal();

	/// \brief Ejecuta el metodo DELETE.
	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo GET.
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo POST.
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo PUT.
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	/// \brief Imprime la operacion.
	virtual void imprimir();
};
};
};

#endif /* OPERACIONPRINCIPAL_H_ */
