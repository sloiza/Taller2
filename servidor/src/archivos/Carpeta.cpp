/*
 * Carpeta.cpp
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#include "Carpeta.h"

using namespace ConexionServidor::BaseDeDatos;

Carpeta::Carpeta() : carpetaLogica(NULL) {}

Carpeta::Carpeta(std::string contenido) : carpetaLogica(NULL)
{
	this->carpetaLogica = new CarpetaLogica(contenido);
}

Carpeta::~Carpeta() {}

void Carpeta::guardar()
{
	this->carpetaLogica->guardar();

	ManagerArchivos manager;
	manager.crearCarpeta( carpetaLogica->getDireccion(), carpetaLogica->getNombre() );
}

void Carpeta::modificar()
{
	this->carpetaLogica->modificar();
}
void Carpeta::eliminar()
{
	this->carpetaLogica->eliminar();

	ManagerArchivos manager;
	manager.eliminarCarpetaVacia( carpetaLogica->getDireccion(), carpetaLogica->getNombre() );
}
std::string Carpeta::recuperar()
{
	this->carpetaLogica->recuperar();
	// this->contenido->recuperar();
}

std::string Carpeta::getPath()
{
	return this->carpetaLogica->getDireccion() + this->carpetaLogica->getNombre();
}

// Metodos de EntidadBD
std::string Carpeta::getValor()
{
	return this->getContenido();
}
std::string Carpeta::getColumnaDeFamilia()
{
	return "no-column";
}
std::string Carpeta::getClave()
{
	return this->carpetaLogica->getPath();
}
