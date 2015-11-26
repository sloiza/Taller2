/// \file VersionDeArchivoPorUsuario.h
/// \date 2015-11-26
/// \brief Clase que representa a la version que tiene un usuario de un archivo.
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
/// \brief Clase que representa a la version que tiene un usuario de un archivo.
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

	/// \brief Constructor.
	VersionDeArchivoPorUsuario();
	/// \brief Destructor.
	virtual ~VersionDeArchivoPorUsuario();

	/// \brief Devuelve el mail del usuario.
	std::string getUsuario();
	/// \brief Devuelve el path del archivo versionado.
	std::string getPathArchivo();
	/// \brief Devuelve la version del archivo que tiene el usuario.
	std::string getVersion();

	/// \brief Setea el mail del usuario.
	void setUsuario(std::string);
	/// \brief Steta el path del archivo versionado.
	void setPathArchivo(std::string);
	/// \brief Setea la version del archivo versionado.
	void setVersion(std::string);

	// Metodos de EntidadDB
	/// \brief Devuelve el valor de la version a guardar en la bd.
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	/// \brief Devuelve el nombre de la columna de familia.
	virtual std::string getColumnaDeFamilia();
	/// \brief Devuelve la clave de la version.
	virtual std::string getClave();

};
};
};

#endif /* VERSIONDEARCHIVOPORUSUARIO_H_ */
