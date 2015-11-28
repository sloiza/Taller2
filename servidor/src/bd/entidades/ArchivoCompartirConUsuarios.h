/// \file ArchivoCompartirConUsuarios.h
/// \date 2015-11-26
/// \brief Clase utilizada para reconocer los usuarios con quien compartir el archivo.
#ifndef ARCHIVOCOMPARTIRCONUSUARIOS_H_
#define ARCHIVOCOMPARTIRCONUSUARIOS_H_

// utiles
#include "../../utiles/utiles.h"
// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
/// \brief Clase utilizada para reconocer los usuarios con quien compartir el archivo.
class ArchivoCompartirConUsuarios : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		NOMBRE,
		DIRECCION,
		EXTENSION,
		USUARIOS
	};
	static const std::string etiquetas[];

	/// \brief Constructor.
	ArchivoCompartirConUsuarios();
	/// \brief Constructor con datos logicos.
	ArchivoCompartirConUsuarios(std::string);
	/// \brief Destructor.
	virtual ~ArchivoCompartirConUsuarios();

	/// \brief Devuelve el nombre del archivo a compartir.
	std::string getNombreArchivo();
	/// \brief Devuelve la direccion del archivo a compartir.
	std::string getDireccionArchivo();
	/// \brief Devuelve el path del archivo a compartir.
	std::string getPathArchivo();
	/// \brief Devuelve la extension del archivo a compartir.
	std::string getExtensionArchivo();

	/// \brief Devuelve los usuarios con quiens voy a compartir el archivo.
	std::vector<std::string> getUsuariosACompartirles();

	// Metodos de EntidadDB
	/// \brief No se usa.
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	/// \brief No se usa.
	virtual std::string getColumnaDeFamilia();
	/// \brief No se usa.
	virtual std::string getClave();
};
};
};

#endif /* ARCHIVOCOMPARTIRCONUSUARIOS_H_ */
