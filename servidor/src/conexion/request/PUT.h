/// \file PUT.h
/// \date 2015-11-26
/// \brief Clase que procesa un metodo OUT.
#ifndef PUT_H_
#define PUT_H_

// STL
#include <string>

// Request
#include "IMetodoREST.h"

namespace ConexionServidor
{
namespace Request
{
/// \brief Clase que procesa un metodo PUT.
class PUT : public IMetodoREST
{
public:
	/// \brief Constructor.
	PUT();
	/// \brief Destructor.
	virtual ~PUT();

	/// \brief Ejecuta las operaciones PUT.
	virtual ConexionServidor::Respuesta ejecutar(ConexionServidor::Operaciones::IOperable* entidad, Utiles::Bytes* contenidoBytes, std::string query);

	/// \brief Devuelve impresion del metodo.
	virtual std::string impresion();
};

};
};

#endif /* PUT_H_ */
