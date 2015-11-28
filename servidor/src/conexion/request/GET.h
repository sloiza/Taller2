/// \file GET.h
/// \date 2015-11-26
/// \brief Clase que procesa un metodo GET.
#ifndef GET_H_
#define GET_H_

// STL
#include <string>

// Request
#include "IMetodoREST.h"

namespace ConexionServidor
{
namespace Request
{
/// \brief Clase que procesa un metodo GET.
class GET : public IMetodoREST
{
public:
	/// \brief Constructor.
	GET();
	/// \brief Destructor.
	virtual ~GET();

	/// \brief Ejecuta las operaciones GET.
	virtual ConexionServidor::Respuesta ejecutar(ConexionServidor::Operaciones::IOperable* entidad, Utiles::Bytes* contenidoBytes, std::string query);

	/// \brief Devuelve impresion del metodo.
	virtual std::string impresion();
};

};
};

#endif /* GET_H_ */
