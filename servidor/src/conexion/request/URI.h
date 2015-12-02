/// \file URI.h
/// \date 2015-11-26
/// \brief Clase wrapper de la URI que accede el cliente.
#ifndef URI_H_
#define URI_H_

// STL
#include <iostream>
#include <string>
#include <vector>

// Base de datos
#include "../../bd/entidades/EntidadBD.h"

namespace ConexionServidor
{
namespace Request
{
/// \brief Clase wrapper de la URI que accede el cliente.
class URI
{
public:
	/// \brief Constructor.
	URI();
	/// \brief Constructor con datos logicos.
	URI(std::string);
	/// \brief Destructor.
	virtual ~URI();

	/// \brief Devuelve uri.
	std::string getURI();
	/// \brief Setea uri.
	void setURI(std::string uri);

	//std::string getEntidadAManejar();
	//ConexionServidor::BaseDeDatos::EntidadDB* getEntidadAManejar();

	/// \brief Devuelve la uri dividida en recursos.
	std::vector<std::string> getRecursosDividos();

private:
	std::string uri;
};

};
};

#endif /* URI_H_ */
