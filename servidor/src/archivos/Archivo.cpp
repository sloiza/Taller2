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


}

void Archivo::modificar() 	// POST
{
	this->archivoLogico->modificar();

	//TODO reemplazarEnDisco: this->eliminar(); this->escribir(bytes);
}
void Archivo::eliminar() 	// DELETE
{
	this->archivoLogico->eliminar();

	//TODO eliminarEnDisco: borrar(this->direccion + this->archivoLogico->getPath);
}
std::string Archivo::recuperar() 	// GET
{
	std::string contenido = this->archivoLogico->recuperar();

	//TODO recuperarDeDisco: this->bytes = bytesRecuperados();

	return contenido;
}

void Archivo::setBytes(Utiles::Bytes* bytes)
{
	this->bytes = bytes;
}
void Archivo::setDireccion(std::string direccion)
{
	this->direccion = direccion;
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
	return this->getDireccion() + "/" + this->archivoLogico->getPath();
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
