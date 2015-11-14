/*
 * Respuesta.cpp
 *
 *  Created on: 31/10/2015
 *      Author: manuel
 */

#include "Respuesta.h"

using namespace ConexionServidor;

const std::string Respuesta::etiquetas[] = {"estado", "mensaje" };

Respuesta::Respuesta() {}

Respuesta::~Respuesta() {}

std::string Respuesta::getEstado()
{
	return this->info->getAtributo(etiquetas[ESTADO], "estadoDefault");
}
std::string Respuesta::getMensaje()
{
	return this->info->getAtributo(etiquetas[MENSAJE], "mensajeDefault");
}

void Respuesta::setEstado(std::string estado)
{
	this->info->setAtributo(etiquetas[ESTADO], estado);
}
void Respuesta::setMensaje(std::string mensaje)
{
	this->info->setAtributo(etiquetas[MENSAJE], mensaje);
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
