/*
 * ManagerArchivos.h
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

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

class ManagerArchivos {
public:
	ManagerArchivos();
	virtual ~ManagerArchivos();

	void escribir(std::string path, Utiles::Bytes* bytes);
	void modificar(std::string path, Utiles::Bytes* bytes);
	void eliminar(std::string path);
	Utiles::Bytes* leer(std::string path);
	bool existe(std::string path);
	void crearCarpeta(std::string direccion, std::string nombre);
	void crearCarpeta(std::string path);
	void eliminarCarpetaVacia(std::string direccion, std::string nombre);
	void eliminarCarpetaVacia(std::string path);

	bool pathEsCarpeta(std::string path);
	bool carpetaEstaVacia(std::string path);

private:

	void delete_folder_tree(const char*);
	int path_is_directory(const char*);
};
};
};

#endif /* MANAGERARCHIVOS_H_ */
