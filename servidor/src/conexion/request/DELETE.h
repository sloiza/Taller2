/// \file DELETE.h
/// \date 2015-11-26
/// \brief Clase que procesa un metodo DELETE.
#ifndef DELETE_H_
#define DELETE_H_

// STL
#include <string>

// Request
#include "IMetodoREST.h"

namespace ConexionServidor
{
namespace Request
{
/// \brief Clase que procesa un metodo DELETE.
class DELETE : public IMetodoREST
{
public:
	/// \brief Constructor.
	DELETE();
	/// \brief Desstructor.
	virtual ~DELETE();

	/// \brief Ejecuta las operaciones DELETE.
	virtual ConexionServidor::Respuesta ejecutar(ConexionServidor::Operaciones::IOperable* entidad, Utiles::Bytes* contenidoBytes, std::string query);

	/// \brief Devuelve impresion del metodo.
	virtual std::string impresion();
};

};
};

#endif /* DELETE_H_ */
