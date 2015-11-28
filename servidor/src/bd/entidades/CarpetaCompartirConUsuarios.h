/// \file CarpetaCompartirConUsuarios.h
/// \date 2015-11-26
/// \brief Clase utilizada para reconocer los usuarios con quien compartir la carpeta.
#ifndef CARPETACOMPARTIRCONUSUARIOS_H_
#define CARPETACOMPARTIRCONUSUARIOS_H_

// utiles
#include "../../utiles/utiles.h"
// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
/// \brief Clase utilizada para reconocer los usuarios con quien compartir la carpeta.
class CarpetaCompartirConUsuarios : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		NOMBRE,
		DIRECCION,
		USUARIOS
	};
	static const std::string etiquetas[];

	/// \brief Constructor.
	CarpetaCompartirConUsuarios();
	/// \brief Constructor con datos logicos.
	CarpetaCompartirConUsuarios(std::string);
	/// \brief Destructor
	virtual ~CarpetaCompartirConUsuarios();


	/// \brief Devuelve nombre de la carpeta a compartir.
	std::string getNombreCarpeta();
	/// \brief Devuelve direccion de la carpeta a compartir.
	std::string getDireccionCarpeta();
	/// \brief Devuelve path de la carpeta a compartir.
	std::string getPathCarpeta();
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

#endif /* CARPETACOMPARTIRCONUSUARIOS_H_ */
