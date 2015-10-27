/*
 * Archivo.cpp
 *
 *  Created on: 25/10/2015
 *      Author: manuel
 */

#include "ArchivoLogico.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string ArchivoLogico::etiquetas[] = {"nombre", "extension", "etiqueta", "fecha_ulti_modi", "usuario_ulti_modi", "propietario", "baja_logica" };

ArchivoLogico::ArchivoLogico() {}

ArchivoLogico::ArchivoLogico(std::string contenido)
{
	this->info->setContenido(contenido);
}

ArchivoLogico::~ArchivoLogico() {}

void ArchivoLogico::setNombre(std::string nombre)
{
	this->info->setAtributo(etiquetas[NOMBRE], nombre);
}
void ArchivoLogico::setExtension(std::string extension)
{
	this->info->setAtributo(etiquetas[EXTENSION], extension);
}
void ArchivoLogico::setEtiqueta(std::string etiqueta)
{
	this->info->setAtributo(etiquetas[ETIQUETA], etiqueta);
}
void ArchivoLogico::setUltimaFechaModif(std::string ultimaFechaModif)
{
	this->info->setAtributo(etiquetas[FECHA_ULTIMA_MODI], ultimaFechaModif);
}
void ArchivoLogico::setUltimoUsuarioModif(std::string ultimoUsuarioModif)
{
	this->info->setAtributo(etiquetas[USUARIO_ULTIMA_MODI], ultimoUsuarioModif);
}
void ArchivoLogico::setPropietario(std::string propietario)
{
	this->info->setAtributo(etiquetas[PROPIETARIO], propietario);
}
void ArchivoLogico::setBajaLogica(std::string bajaLogica)
{
	this->info->setAtributo(etiquetas[BAJA_LOGICA], bajaLogica);
}

std::string ArchivoLogico::getNombre()
{
	return this->info->getAtributo(etiquetas[NOMBRE], "nombreDefault");
}
std::string ArchivoLogico::getExtension()
{
	return this->info->getAtributo(etiquetas[EXTENSION], "extensionDefault");
}
std::string ArchivoLogico::getEtiqueta()
{
	return this->info->getAtributo(etiquetas[ETIQUETA], "etiquetaDefault");
}
std::string ArchivoLogico::getUltimaFechaModif()
{
	return this->info->getAtributo(etiquetas[FECHA_ULTIMA_MODI], "fechaDefault");
}
std::string ArchivoLogico::getUltimoUsuarioModif()
{
	return this->info->getAtributo(etiquetas[USUARIO_ULTIMA_MODI], "usuarioDefault");
}
std::string ArchivoLogico::getPropietario()
{
	return this->info->getAtributo(etiquetas[PROPIETARIO], "propietarioDefault");
}
std::string ArchivoLogico::getBajaLogica()
{
	return this->info->getAtributo(etiquetas[BAJA_LOGICA], "bajaDefault");
}

std::string ArchivoLogico::getPath()
{
	return this->getNombre() + "." + this->getExtension();
}

// Metodos de EntidadDB
std::string ArchivoLogico::getValor()
{
	return this->info->getContenido();
}

std::string ArchivoLogico::getColumnaDeFamilia()
{
	return "file";
}

std::string ArchivoLogico::getClave()
{
	return this->getNombre() + this->getExtension();
}


