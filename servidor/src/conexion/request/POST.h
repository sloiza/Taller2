/// \file POST.h
/// \date 2015-11-26
/// \brief Clase que procesa un metodo POST.
#ifndef POST_H_
#define POST_H_

// STL
#include <string>

// Request
#include "IMetodoREST.h"

namespace ConexionServidor
{
namespace Request
{
/// \brief Clase que procesa un metodo POST.
class POST : public IMetodoREST
{
public:
	/// \brief Constructor.
	POST();
	/// \brief Destructor.
	virtual ~POST();

	/// \brief Ejecuta las operaciones POST.
	virtual ConexionServidor::Respuesta ejecutar(ConexionServidor::Operaciones::IOperable* entidad, Utiles::Bytes* contenidoBytes, std::string query);

	/// \brief Devuelve impresion del metodo.
	virtual std::string impresion();
};

};
};

#endif /* POST_H_ */
