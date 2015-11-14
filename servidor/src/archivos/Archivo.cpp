/*
 * Archivo.cpp
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#include "Archivo.h"

using namespace ConexionServidor::BaseDeDatos;

Archivo::Archivo() : archivoLogico(NULL) , bytes(NULL){}

Archivo::Archivo(std::string contenidoLogico) : archivoLogico(NULL), bytes(NULL)
{
	this->archivoLogico = new ArchivoLogico(contenidoLogico);
}

Archivo::~Archivo()
{
	if ( this->archivoLogico != NULL)
	{
		delete this->archivoLogico;
		this->archivoLogico = NULL;
	}

	if ( this->bytes != NULL)
	{
		delete this->bytes;
		this->bytes = NULL;
	}
}

void Archivo::guardar()
{
	this->archivoLogico->guardar();

	ManagerArchivos manager;
	manager.escribir( archivoLogico->getPath(), this->getBytes() );
}

void Archivo::modificar() 	// POST
{
	this->archivoLogico->modificar();

	this->eliminar();
	this->guardar();
}
void Archivo::eliminar() 	// DELETE
{
	this->archivoLogico->eliminar();

	ManagerArchivos manager;
	manager.eliminar( archivoLogico->getPath() );
}
std::string Archivo::recuperar() 	// GET
{
	this->archivoLogico->recuperar();
	ManagerArchivos manager;
	this->bytes = manager.leer( this->archivoLogico->getPath() );

	return this->bytes->getStringDeBytes();
}

void Archivo::setBytes(Utiles::Bytes* bytes)
{
	this->bytes = bytes;
}
void Archivo::setDireccion(std::string direccion)
{
	this->direccion = direccion;
}

const char* Archivo::getTiraDeBytes()
{
	//return this->bytes->getBytes();
	return this->bytes->getStringDeBytes().c_str();
}
Utiles::Bytes* Archivo::getBytes()
{
	return this->bytes;
}
std::string Archivo::getDireccion()
{
	return this->direccion;
}
std::string Archivo::getPath()
{
	//return this->getDireccion() + "/" + this->archivoLogico->getPath();
	return this->archivoLogico->getPath();
}
bool Archivo::existeFisicamente()
{
	ManagerArchivos manager;
	return manager.existe( this->getPath() );
}
void Archivo::eliminarFisicamente()
{
	ManagerArchivos manager;
	manager.eliminar( archivoLogico->getPath() );
}
void Archivo::guardarFisicamente()
{
	ManagerArchivos manager;
	manager.escribir( archivoLogico->getPath(), this->getBytes() );
}

// Metodos de EntidadBD
std::string Archivo::getValor()
{
	std::string bytesString(this->bytes->getBytes());
	return bytesString;
}
std::string Archivo::getColumnaDeFamilia()
{
	return "no-column";
}
std::string Archivo::getClave()
{
	return this->getPath();
}
std::string Archivo::getContenido()
{
	return this->archivoLogico->getContenido();
}
