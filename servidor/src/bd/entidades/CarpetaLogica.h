/// \file CarpetaLogica.h
/// \date 2015-11-26
/// \brief Clase que representa a una carpeta logica.
#ifndef CARPETALOGICA_H_
#define CARPETALOGICA_H_

// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
/// \brief Clase que representa a una carpeta logica.
class CarpetaLogica : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		NOMBRE,
		ETIQUETA,
		FECHA_ULTIMA_MODI,
		USUARIO_ULTIMA_MODI,
		PROPIETARIO,
		BAJA_LOGICA,
		DIRECCION,
	};
	static const std::string etiquetas[];

	/// \brief Constructor
	CarpetaLogica();
	/// \brief Constructor con datos logicos.
	CarpetaLogica(std::string);
	/// \brief Destructor
	virtual ~CarpetaLogica();

	/// \brief Setea nombre de la carpeta.
	void setNombre(std::string);
	/// \brief Setea ultima fecha de modificacion de la carpeta.
	void setUltimaFechaModif(std::string);
	/// \brief Setea mail del ultimo usuario que modifica e la carpeta.
	void setUltimoUsuarioModif(std::string);
	/// \brief Setea el mail del propietario de la carpeta.
	void setPropietario(std::string);
	/// \brief Setea el estado logico de la carpeta.
	void setBajaLogica(std::string);
	/// \brief Setea la direccion de la carpeta.
	void setDireccion(std::string);

	/// \brief Devuelve nombre de la carpeta.
	std::string getNombre();
	/// \brief Devuelve ultima fecha de modificacion de la carpeta.
	std::string getUltimaFechaModif();
	/// \brief Devuelve mail de ultimo usuario que modifico de la carpeta.
	std::string getUltimoUsuarioModif();
	/// \brief Devuelve mail del propietario de la carpeta.
	std::string getPropietario();
	/// \brief Devuelve el estado logico de la carpeta.
	std::string getBajaLogica();
	/// \brief Devuelve la direccion de la carpeta.
	std::string getDireccion();

	/// \brief Devuelve path de la carpeta.
	std::string getPath();

	/// \brief Agrega etiqueta a la carpeta.
	std::vector<std::string> getEtiquetas();
	/// \brief Devuelve etiquetas de la carpeta.
	void agregarEtiqueta(std::string);

	// Metodos de EntidadDB
	/// \brief Devuelve el valor de la carpeta logica a guardar en la bd.
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	/// \brief Devuelve el nombre de la columna de familia.
	virtual std::string getColumnaDeFamilia();
	/// \brief Devuelve la clave de la carpeta logica.
	virtual std::string getClave();
};
};
};

#endif /* CARPETALOGICA_H_ */
