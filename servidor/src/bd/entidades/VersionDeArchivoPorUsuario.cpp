/*
 * VersionDeArchivoPorUsuario.cpp
 *
 *  Created on: 22/11/2015
 *      Author: manuel
 */

#include "VersionDeArchivoPorUsuario.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string VersionDeArchivoPorUsuario::etiquetas[] = {"usuario", "path_archivo", "version" };

VersionDeArchivoPorUsuario::VersionDeArchivoPorUsuario() {}

VersionDeArchivoPorUsuario::~VersionDeArchivoPorUsuario() {}

std::string VersionDeArchivoPorUsuario::getUsuario()
{
	return this->info->getAtributo(etiquetas[USUARIO], "usuarioDefault");
}
std::string VersionDeArchivoPorUsuario::getPathArchivo()
{
	return this->info->getAtributo(etiquetas[PATH_ARCHIVO], "archivoDefault");
}
std::string VersionDeArchivoPorUsuario::getVersion()
{
	return this->info->getAtributo(etiquetas[VERSION], "versionDefault");
}
void VersionDeArchivoPorUsuario::setUsuario(std::string usuario)
{
	this->info->setAtributo(etiquetas[USUARIO], usuario);
}
void VersionDeArchivoPorUsuario::setPathArchivo(std::string archivo)
{
	this->info->setAtributo(etiquetas[PATH_ARCHIVO], archivo);
}
void VersionDeArchivoPorUsuario::setVersion(std::string version)
{
	this->info->setAtributo(etiquetas[VERSION], version);
}

// Metodos de EntidadDB
std::string VersionDeArchivoPorUsuario::getValor()
{
	return this->info->getContenido();
}

std::string VersionDeArchivoPorUsuario::getColumnaDeFamilia()
{
	return "file";
}

std::string VersionDeArchivoPorUsuario::getClave()
{
	return "v-" + this->getUsuario() + "-" + this->getPathArchivo();
}

