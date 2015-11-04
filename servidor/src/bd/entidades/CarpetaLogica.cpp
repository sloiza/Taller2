/*
 * CarpetaLogica.cpp
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#include "CarpetaLogica.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string CarpetaLogica::etiquetas[] = {"nombre", "etiqueta", "fecha_ulti_modi", "usuario_ulti_modi", "propietario", "baja_logica", "direccion" };

CarpetaLogica::CarpetaLogica() {}

CarpetaLogica::CarpetaLogica(std::string contenido)
{
	this->info->setContenido(contenido);
}

CarpetaLogica::~CarpetaLogica() {}


void CarpetaLogica::setNombre(std::string nombre)
{
	this->info->setAtributo(etiquetas[NOMBRE], nombre);
}
void CarpetaLogica::setEtiqueta(std::string etiqueta)
{
	this->info->setAtributo(etiquetas[ETIQUETA], etiqueta);
}
void CarpetaLogica::setUltimaFechaModif(std::string ultimaFechaModif)
{
	this->info->setAtributo(etiquetas[FECHA_ULTIMA_MODI], ultimaFechaModif);
}
void CarpetaLogica::setUltimoUsuarioModif(std::string ultimoUsuarioModif)
{
	this->info->setAtributo(etiquetas[USUARIO_ULTIMA_MODI], ultimoUsuarioModif);
}
void CarpetaLogica::setPropietario(std::string propietario)
{
	this->info->setAtributo(etiquetas[PROPIETARIO], propietario);
}
void CarpetaLogica::setBajaLogica(std::string bajaLogica)
{
	this->info->setAtributo(etiquetas[BAJA_LOGICA], bajaLogica);
}
void CarpetaLogica::setDireccion(std::string direccion)
{
	this->info->setAtributo(etiquetas[DIRECCION], direccion);
}

std::string CarpetaLogica::getNombre()
{
	return this->info->getAtributo(etiquetas[NOMBRE], "nombreDefault");
}
std::string CarpetaLogica::getEtiqueta()
{
	return this->info->getAtributo(etiquetas[ETIQUETA], "etiquetaDefault");
}
std::string CarpetaLogica::getUltimaFechaModif()
{
	return this->info->getAtributo(etiquetas[FECHA_ULTIMA_MODI], "fechaDefault");
}
std::string CarpetaLogica::getUltimoUsuarioModif()
{
	return this->info->getAtributo(etiquetas[USUARIO_ULTIMA_MODI], "usuarioDefault");
}
std::string CarpetaLogica::getPropietario()
{
	return this->info->getAtributo(etiquetas[PROPIETARIO], "propietarioDefault");
}
std::string CarpetaLogica::getBajaLogica()
{
	return this->info->getAtributo(etiquetas[BAJA_LOGICA], "bajaDefault");
}
std::string CarpetaLogica::getDireccion()
{
	return this->info->getAtributo(etiquetas[DIRECCION], "direccionDefault");
}

std::string CarpetaLogica::getPath()
{
	return this->getDireccion() + this->getNombre();
}

// Metodos de EntidadDB
std::string CarpetaLogica::getValor()
{
	return this->info->getContenido();
}

std::string CarpetaLogica::getColumnaDeFamilia()
{
	return "file";
}

std::string CarpetaLogica::getClave()
{
	return this->getPath();
}
