/*
 * InfoOperaciones.h
 *
 *  Created on: 31/10/2015
 *      Author: manuel
 */

#ifndef INFOOPERACIONES_H_
#define INFOOPERACIONES_H_

// STL
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class InfoOperaciones {
public:
	InfoOperaciones();
	virtual ~InfoOperaciones();

	enum OPERACIONES
	{
		PRINCIPAL,
		USUARIOS,
		ARCHIVOS,
		CARPETAS,
		COMPARTIR_ARCHIVO,
		COMPARTIR_CARPETA,
		DESCARGAR
	};

	static const std::string nombresRecursos[];
};
};
};

#endif /* INFOOPERACIONES_H_ */
