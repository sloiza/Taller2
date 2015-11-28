/// \file InfoOperaciones.h
/// \date 2015-11-26
/// \brief Clase que contiene informacion que utilizan las operaciones.
#ifndef INFOOPERACIONES_H_
#define INFOOPERACIONES_H_

// STL
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Clase que contiene informacion que utilizan las operaciones.
class InfoOperaciones {
public:
	/// \brief Constructor.
	InfoOperaciones();
	/// \brief Destructor.
	virtual ~InfoOperaciones();

	enum OPERACIONES
	{
		PRINCIPAL,
		USUARIOS,
		ARCHIVOS,
		CARPETAS,
		COMPARTIR_ARCHIVO,
		COMPARTIR_CARPETA,
		DESCARGAR,
		PAPELERA,
		BUSCAR
	};

	static const std::string nombresRecursos[];

	static const std::string carpetaRaiz;

	static const std::string compartidos;

	static const std::string papelera;

	static const std::string carpetaArchivosPorUsuario;
};
};
};

#endif /* INFOOPERACIONES_H_ */
