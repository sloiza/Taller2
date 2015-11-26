

#ifndef VERSIONDEARCHIVOPORUSUARIO_H_
#define VERSIONDEARCHIVOPORUSUARIO_H_

// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class VersionDeArchivoPorUsuario : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		USUARIO,
		PATH_ARCHIVO,
		VERSION
	};
	static const std::string etiquetas[];

	VersionDeArchivoPorUsuario();
	virtual ~VersionDeArchivoPorUsuario();

	std::string getUsuario(), getPathArchivo(), getVersion();
	void setUsuario(std::string), setPathArchivo(std::string), setVersion(std::string);

	// Metodos de EntidadDB
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();

};
};
};

#endif /* VERSIONDEARCHIVOPORUSUARIO_H_ */
