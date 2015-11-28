/// \file ManagerArchivos.h
/// \date 2015-11-26
/// \brief Clase que maneja fisicamente los arhicovs y carpeta.
#ifndef MANAGERARCHIVOS_H_
#define MANAGERARCHIVOS_H_

// utiles
#include "../utiles/Log.h"
#include "../utiles/Bytes.h"

// STL
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

namespace ConexionServidor
{
namespace BaseDeDatos
{

/// \brief Clase que maneja fisicamente los arhicovs y carpeta.
class ManagerArchivos {
public:
	/// \brief Constructor.
	ManagerArchivos();
	/// \brief Destructor.
	virtual ~ManagerArchivos();

	/// \brief Escribe bytes en el path indicado.
	void escribir(std::string path, Utiles::Bytes* bytes);
	/// \brief Modifica los bytes del path indicado.
	void modificar(std::string path, Utiles::Bytes* bytes);
	/// \brief Elimina los bytes del path indicado.
	void eliminar(std::string path);
	/// \brief Recuepra los bytes del path indicado.
	Utiles::Bytes* leer(std::string path);
	/// \brief Chequea si existe el path indicado.
	bool existe(std::string path);
	/// \brief Crea carpeta con el nombre indicado, en la direccion indicada.
	void crearCarpeta(std::string direccion, std::string nombre);
	/// \brief Crea carpeta en el path indicado.
	void crearCarpeta(std::string path);
	/// \brief Elimina la carpeta vacia con direccion y nombre indicado.
	void eliminarCarpetaVacia(std::string direccion, std::string nombre);
	/// \brief Elimina la carpeta vacia con el path indicado.
	void eliminarCarpetaVacia(std::string path);

	/// \brief Chequea si la carpeta esta vacia.
	bool carpetaEstaVacia(std::string path);
};
};
};

#endif /* MANAGERARCHIVOS_H_ */
