
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

class OperacionErrorURL: public IOperable {
public:
	OperacionErrorURL();
	virtual ~OperacionErrorURL();

	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

};
};
};

#endif /* OPERACIONERRORURL_H_ */
