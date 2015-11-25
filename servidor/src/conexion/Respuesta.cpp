/*
 * Respuesta.cpp
 *
 *  Created on: 31/10/2015
 *      Author: manuel
 */

#include "Respuesta.h"

using namespace ConexionServidor;

const std::string Respuesta::etiquetas[] = {"estado", "mensaje", "bytes" };

Respuesta::Respuesta() : esDescarga(false) {}

Respuesta::~Respuesta() {}

std::string Respuesta::getEstado()
{
	return this->info->getAtributo(etiquetas[ESTADO], "estadoDefault");
}
std::string Respuesta::getMensaje()
{
	return this->info->getAtributo(etiquetas[MENSAJE], "mensajeDefault");
}
std::string Respuesta::getBytes()
{
	return this->info->getAtributo(etiquetas[BYTES], "bytesDefault");
}
bool Respuesta::getEsDescarga()
{
	return this->esDescarga;
}
std::string Respuesta::getPathDelArchivoADescargar()
{
	return this->pathArchivoADescargar;
}

void Respuesta::setEstado(std::string estado)
{
	this->info->setAtributo(etiquetas[ESTADO], estado);
}
void Respuesta::setMensaje(std::string mensaje)
{
	this->info->setAtributo(etiquetas[MENSAJE], mensaje);
}
void Respuesta::setBytes(std::string bytesEnString)
{
	this->info->setAtributo(etiquetas[BYTES], bytesEnString);
}
void Respuesta::setEsDescarga(bool esDescarga)
{
	this->esDescarga = esDescarga;
}
void Respuesta::setPathDelArchivoADescargar(std::string pathArchivoADescargar)
{
	this->pathArchivoADescargar = pathArchivoADescargar;
}

// Metodos de EntidadDB
std::string Respuesta::getValor()
{
	return this->info->getContenido();
}

std::string Respuesta::getColumnaDeFamilia()
{
	return "respuesta";
}

std::string Respuesta::getClave()
{
	return this->getMensaje();
}
