/*
 * CarpetaCompartirConUsuarios.cpp
 *
 *  Created on: 14/11/2015
 *      Author: manuel
 */

#include "CarpetaCompartirConUsuarios.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string CarpetaCompartirConUsuarios::etiquetas[] = {"nombre", "direccion", "usuarios" };

CarpetaCompartirConUsuarios::CarpetaCompartirConUsuarios() {}

CarpetaCompartirConUsuarios::CarpetaCompartirConUsuarios(std::string contenido)
{
	this->info->setContenido( contenido );
}

CarpetaCompartirConUsuarios::~CarpetaCompartirConUsuarios() {}

std::string CarpetaCompartirConUsuarios::getNombreCarpeta()
{
	return this->info->getAtributo(etiquetas[NOMBRE], "nombreDefault");
}
std::string CarpetaCompartirConUsuarios::getDireccionCarpeta()
{
	return this->info->getAtributo(etiquetas[DIRECCION], "direccionDefault");
}
std::string CarpetaCompartirConUsuarios::getPathCarpeta()
{
	return this->getDireccionCarpeta() + this->getNombreCarpeta();
}
std::vector<std::string> CarpetaCompartirConUsuarios::getUsuariosACompartirles()
{
	return this->info->getListaDeValorDeAtributo(etiquetas[USUARIOS], "usuariosDefault");
}

// Metodos de EntidadDB
std::string ContenidoPorCarpeta::getValor()
{
	return this->info->getContenido();
}

std::string ContenidoPorCarpeta::getColumnaDeFamilia()
{
	return "file";
}

std::string ContenidoPorCarpeta::getClave()
{
	//return "contenido" + this->getPath();
	return "noImportaPorqNuncaSeAlmacena";
}
