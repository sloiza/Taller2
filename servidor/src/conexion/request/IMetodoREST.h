/// \file IMetodoREST.h
/// \date 2015-11-26
/// \brief Interfaz que implementan un metodo REST.
#ifndef IMETODOREST_H_
#define IMETODOREST_H_

// conexion
#include "../../conexion/Respuesta.h"
// Base de datos
#include "../../operaciones/IOperable.h"
#include "../../bd/JsonInfo.h"

// utiles
#include "../../utiles/Bytes.h"

namespace ConexionServidor
{

namespace Request
{
/// \brief Interfaz que implementan un metodo REST.
class IMetodoREST {
public:
	/// \brief Constructor.
	IMetodoREST() {}
	/// \brief Destructor.
	virtual ~IMetodoREST() {}

	/// \brief Ejecuta las operaciones del metodo.
	virtual ConexionServidor::Respuesta ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenidoBytes, std::string query) = 0;

	/// \brief Devuelve impresion del metodo.
	virtual std::string impresion() = 0;
};
};
};

#endif /* IMETODOREST_H_ */
