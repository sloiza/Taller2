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
};
};
};

#endif /* MANAGERARCHIVOS_H_ */
