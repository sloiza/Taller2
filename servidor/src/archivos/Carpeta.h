/// \file Carpeta.h
/// \date 2015-11-26
/// \brief Clase que representa a una carpeta fisica y logica.
#ifndef CARPETA_H_
#define CARPETA_H_

// entidades
#include "../bd/entidades/EntidadBD.h"
#include "../bd/entidades/CarpetaLogica.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"

// manager archivos
#include "../archivos/ManagerArchivos.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

/// \brief Clase que representa a una carpeta fisica y logica.
class Carpeta : public EntidadDB
{
public:
	/// \brief Constructor.
	Carpeta();
	/// \brief /// \brief con datos logicos.
	Carpeta(std::string datosLogicos);
	/// \brief Destructor
	virtual ~Carpeta();

	/// \brief Guarda fisica y logicamente la carpeta. Sobreescribe el metodo de EntidadDB.
	virtual void guardar(); 		// PUT
	/// \brief Modifica fisica y logicamente la carpeta. Sobreescribe el metodo de EntidadDB.
	virtual void modificar(); 	// POST
	/// \brief Elimina fisica y logicamente la carpeta. Sobreescribe el metodo de EntidadDB.
	virtual void eliminar(); 	// DELETE
	/// \brief Recupera fisica y logicamente la carpeta, devolviendo los datos lógicos. Sobreescribe el metodo de EntidadDB.
	virtual std::string recuperar(); 	// GET

	/// \brief Setea nombre de carpeta.
	void setNombre(std::string);
	/// \brief Setea etiqueta de carpeta.
	//void setEtiqueta(std::string);
	/// \brief Setea la ultima fecha de modificacion de carpeta.
	void setUltimaFechaModif(std::string);
	/// \brief Setea el mail del último usuario que modifico la carpeta.
	void setUltimoUsuarioModif(std::string);
	/// \brief Setea el mail propietario de carpeta.
	void setPropietario(std::string);
	/// \brief Setea si la carpeta esta dada de baja lógica.
	void setBajaLogica(std::string);
	/// \brief Setea direccion de carpeta.
	void setDireccion(std::string);

	/// \brief Devuelve nombre de carpeta.
	std::string getNombre();
	/// \brief Devuelve etiqueta de carpeta.
	//std::string getEtiqueta();
	/// \brief Devuelve fecha de la última modificación de carpeta.
	std::string getUltimaFechaModif();
	/// \brief Devuelve mail del último usuario que modifica la carpeta.
	std::string getUltimoUsuarioModif();
	/// \brief Devuelve mail del propietario de carpeta.
	std::string getPropietario();
	/// \brief Devuelve el estado lógico de la carpeta.
	std::string getBajaLogica();
	/// \brief Devuelve la direccion de la carpeta.
	std::string getDireccion();

	/// \brief Devuelve el path de la carpeta.
	std::string getPath();

	/// \brief Chequea si existe fisicamente la carpeta.
	bool existeFisicamente();
	/// \brief Chequea si la carpeta fisica esta vacia.
	bool estaVacia();

	// Metodos de EntidadDB
	virtual void setContenido(std::string);

	/// \brief Devuelve el valor de la carpeta a guardar en la bd.
	virtual std::string getValor();

	/// \brief Devuelve la lista de etiquetas del archivo.
	std::vector<std::string> getEtiquetas();
	/// \brief Agrega una etiqueta al archivo.
	void agregarEtiqueta(std::string);

protected:
	// Metodos de EntidadDB
	/// \brief Devuelve el nombre de la columna de familia.
	virtual std::string getColumnaDeFamilia();
	/// \brief Devuelve la clave de la carpeta.
	virtual std::string getClave();

private:

	CarpetaLogica* carpetaLogica;
	ContenidoPorCarpeta* contenido;

};
};
};

#endif /* CARPETA_H_ */
