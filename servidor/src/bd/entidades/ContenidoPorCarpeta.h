/// \file ContenidoPorCarpeta.h
/// \date 2015-11-26
/// \brief Clase que representa al contenido de una carpeta logica.
#ifndef CONTENIDOPORCARPETA_H_
#define CONTENIDOPORCARPETA_H_

// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
/// \brief Clase que representa al contenido de una carpeta logica.
class ContenidoPorCarpeta : public EntidadDB
{
public:

	enum enumEtiquetas
	{
		NOMBRE,
		DIRECCION,
		ARCHIVOS,
		CARPETAS
	};
	static const std::string etiquetas[];

	/// \brief Constructor.
	ContenidoPorCarpeta();
	/**
	 * @brief Constructor: Genera una instancia de la entidad a partir de un string con el contenido.
	 */
	ContenidoPorCarpeta(std::string contenido);
	/// \brief Destructor
	virtual ~ContenidoPorCarpeta();

	 /// \brief Setea el path de la carpeta.
	void setPath(std::string);
	/// \brief Setea el nombre de la carpeta.
	void setNombre(std::string);
	/// \brief Setea la direccion de la carpeta.
	void setDireccion(std::string);
	/// \brief Agrega path de archivo a la carpeta.
	void agregarArchivo(std::string);
	/// \brief Agrega path de carpeta a la carpeta.
	void agregarCarpeta(std::string);
	/// \brief Elimina path de archivo de la carpeta.
	void eliminarArchivo(std::string);
	/// \brief Elimina path de carpeta de la carpeta.
	void eliminarCarpeta(std::string);
	/// \brief Elimina todos los archivos.
	void eliminarTodosLosArchivos();
	/// \brief Elimina todas las carpetas.
	void eliminarTodasLosCarpetas();

	/// \brief Devuelve el path de la carpeta.
	std::string getPath();
	/// \brief Devuelve el nombre de la carpeta.
	std::string getNombre();
	/// \brief Devuelve la direccion de la carpeta.
	std::string getDireccion();
	/// \brief Devuelve la lista de archivos de la carpeta.
	std::vector<std::string> getArchivos();
	/// \brief Devuelve la lista de carpeta de la carpeta.
	std::vector<std::string> getCarpetas();

	// Metodos de EntidadDB
	/// \brief Devuelve el valor del contenido logico a guardar en la bd.
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	/// \brief Devuelve el nombre de la columna de familia.
	virtual std::string getColumnaDeFamilia();
	/// \brief Devuelve la clave del contenido logico.
	virtual std::string getClave();

};
};
};

#endif /* CONTENIDOPORCARPETA_H_ */
