/// \file OperacionErrorURL.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de una URI no mapeada.
#ifndef OPERACIONERRORURL_H_
#define OPERACIONERRORURL_H_

// operaciones
#include "IOperable.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Clase que realiza las operaciones de una URI no mapeada.
class OperacionErrorURL: public IOperable {
public:
	/// \brief Constructor.
	OperacionErrorURL();
	/// \brief Destructor.
	virtual ~OperacionErrorURL();

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

};
};
};

#endif /* OPERACIONERRORURL_H_ */
