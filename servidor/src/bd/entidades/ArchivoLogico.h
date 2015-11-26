/// \file ArchivoLogico.h
/// \date 2015-11-26
/// \brief Clase que representa a un archivo logico.
#ifndef ARCHIVOLOGICO_H_
#define ARCHIVOLOGICO_H_

// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
/// \brief Clase que representa a un archivo logico.
class ArchivoLogico: public EntidadDB
{

public:

	enum enumEtiquetas
	{
		NOMBRE,
		EXTENSION,
		ETIQUETA,
		FECHA_ULTIMA_MODI,
		USUARIO_ULTIMA_MODI,
		PROPIETARIO,
		BAJA_LOGICA,
		DIRECCION,
		COMPARTIDO_CON,
		VERSION
	};

	static const std::string etiquetas[];

	/// \brief Constructor.
	ArchivoLogico();
	/// \brief Constructor con datos lógicos.
	ArchivoLogico(std::string contenido);
	/// \brief Destructor.
	virtual ~ArchivoLogico();

	/// \brief Setea nombre del archivo.
	void setNombre(std::string);
	/// \brief Setea extension del archivo.
	void setExtension(std::string);
	/// \brief Setea ultima fecha de modificacion del archivo.
	void setUltimaFechaModif(std::string);
	/// \brief Setea mail del ultimo usuario que modifica el archivo.
	void setUltimoUsuarioModif(std::string);
	/// \brief Setea el mail del propietario del archivo.
	void setPropietario(std::string);
	/// \brief Setea el estado logico del archivo.
	void setBajaLogica(std::string);
	/// \brief Setea la direccion del archivo.
	void setDireccion(std::string);
	/// \brief Setea el numero de version del archivo.
	void setVersion(std::string);

	/// \brief Devuelve nombre del archivo.
	std::string getNombre();
	/// \brief Devuelve extension del archivo.
	std::string getExtension();
	/// \brief Devuelve ultima fecha de modificacion del archivo.
	std::string getUltimaFechaModif();
	/// \brief Devuelve mail de ultimo usuario que modifico del archivo.
	std::string getUltimoUsuarioModif();
	/// \brief Devuelve mail del propietario del archivo.
	std::string getPropietario();
	/// \brief Devuelve el estado logico del archivo.
	std::string getBajaLogica();
	/// \brief Devuelve la direccion del archivo.
	std::string getDireccion();
	/// \brief Devuelve nombre y extension del archivo.
	std::string getNombreYExtension();
	/// \brief Devuelve version del archivo.
	std::string getVersion();

	/// \brief Devuelve path del archivo.
	std::string getPath();
	/// \brief Setea path del archivo.
	void setPath(std::string);

	/// \brief Agrega etiqueta al archivo.
	void agregarEtiqueta(std::string);
	/// \brief Devuelve etiquetas del archivo.
	std::vector<std::string> getEtiquetas();

	/// \brief Agrega mail de usuario que se le compartio el archivo.
	void agregarCompartidoCon(std::string);
	/// \brief Devuelve lista de mails de usuario a los que se les compartio el archivo.
	std::vector<std::string> getCompartidoCon();

	// Metodos de EntidadDB
	/// \brief Devuelve el valor del archivo logico a guardar en la bd.
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	/// \brief Devuelve el nombre de la columna de familia.
	virtual std::string getColumnaDeFamilia();
	/// \brief Devuelve la clave del archivo logico.
	virtual std::string getClave();

};
};
};

#endif /* ARCHIVOLOGICO_H_ */
