/// \file Archivo.h
/// \date 2015-11-26
/// \brief Clase que representa a un archivo fisico y logico.
#ifndef ARCHIVO_H_
#define ARCHIVO_H_

// utiles
#include "../utiles/utiles.h"
#include "../utiles/Bytes.h"

// entidades
#include "../bd/entidades/EntidadBD.h"
#include "../bd/entidades/ArchivoLogico.h"

// manager archivos
#include "../archivos/ManagerArchivos.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
/// \brief Clase utilizada para administrar los archivos.
class Archivo: public EntidadDB
{
public:
	/// \brief Constructor.
	Archivo();
	/// \brief Constructor con datos logicos.
	Archivo(std::string datosLogicos);
	/// \brief Destructor.
	virtual ~Archivo();

	/// \brief Setea los bytes del archivo con el wrapper Bytes.
	void setBytes(Utiles::Bytes* bytes);
	/// \brief Setea la direccion ( path de la carpeta ) del archivo.
	void setDireccion(std::string);

	/// \brief Devuelve los bytes del archivo en la wrapper Bytes.
	Utiles::Bytes* getBytes();
	/// \brief Devuelve la tira de bytes del archivo.
	const char* getTiraDeBytes();
	/// \brief Devuelve la direccion ( path de la carpeta ) del archivo.
	std::string getDireccion();
	/// \brief Devuelve el path del archivo.
	std::string getPath();

	/// \brief Chequea si existe fisicamente el archivo.
	bool existeFisicamente();
	/// \brief Elimina fisicamente el archivo.
	void eliminarFisicamente();
	/// \brief Guarda en disco el archivo.
	void guardarFisicamente();

	// Metodos de EntidadDB
	/// \brief Devuelve el valor del archivo a guardar en la bd.
	virtual std::string getValor();

	/// \brief Guarda fisica y logicamente el archivo. Sobreescribe el metodo de EntidadDB.
	virtual void guardar(); 		// PUT
	/// \brief Modifica fisica y logicamente el archivo. Sobreescribe el metodo de EntidadDB.
	virtual void modificar(); 	// POST
	/// \brief Elimina fisicamente y da de baja logica el archivo. Sobreescribe el metodo de EntidadDB.
	virtual void eliminar(); 	// DELETE
	/// \brief Recupera fisica y logicamente el archivo, devolviendo los datos logicos. Sobreescribe el metodo de EntidadDB.
	virtual std::string recuperar(); 	// GET

	/// \brief Devuelve el contenido en un json.
	virtual std::string getContenido();

protected:
	// Metodos de EntidadDB
	/// \brief Devuelve el nombre de la columna de familia.
	virtual std::string getColumnaDeFamilia();
	/// \brief Devuelve la clave del archivo.
	virtual std::string getClave();

	ArchivoLogico* archivoLogico;
	std::string direccion;
	Utiles::Bytes* bytes;
};
};
};


#endif /* ARCHIVO_H_ */
