

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

class IMetodoREST {
public:
	IMetodoREST() {}
	virtual ~IMetodoREST() {}

	virtual ConexionServidor::Respuesta ejecutar(ConexionServidor::Operaciones::IOperable* operacion, Utiles::Bytes* contenidoBytes, std::string query) = 0;

	virtual std::string impresion() = 0;
};
};
};

#endif /* IMETODOREST_H_ */
