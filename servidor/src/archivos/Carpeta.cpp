/*
 * Carpeta.cpp
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#include "Carpeta.h"

using namespace ConexionServidor::BaseDeDatos;

Carpeta::Carpeta() : carpetaLogica(NULL) , contenido(NULL)
{
	this->carpetaLogica = new CarpetaLogica();
	this->contenido = new ContenidoPorCarpeta();
}

Carpeta::Carpeta(std::string contenido) : carpetaLogica(NULL), contenido(NULL)
{
	this->carpetaLogica = new CarpetaLogica(contenido);
	this->contenido = new ContenidoPorCarpeta();
	this->contenido->setNombre( carpetaLogica->getNombre() );
	this->contenido->setDireccion( carpetaLogica->getDireccion() );
}

Carpeta::~Carpeta()
{
	if ( carpetaLogica != NULL )
	{
		delete carpetaLogica;
		carpetaLogica = NULL;
	}
	if ( contenido != NULL )
	{
		delete contenido;
		contenido = NULL;
	}
}

// ---------- METODOS DE ENTIDAD ------------ //
void Carpeta::guardar()
{
	this->carpetaLogica->guardar();
	this->contenido->guardar();

	ManagerArchivos manager;
	manager.crearCarpeta( carpetaLogica->getDireccion(), carpetaLogica->getNombre() );
}

void Carpeta::modificar()
{
	this->carpetaLogica->modificar();
	//this->contenido->modificar();
}
void Carpeta::eliminar()
{
	ManagerArchivos manager;
	manager.eliminarCarpetaVacia( carpetaLogica->getDireccion(), carpetaLogica->getNombre() );

	if ( manager.existe( carpetaLogica->getPath() ) == false )
	{// si pudo borrarla, entonces elimino sus metadatos
		this->carpetaLogica->eliminar();
		this->contenido->eliminar();
	}
}
std::string Carpeta::recuperar()
{
	this->carpetaLogica->recuperar();
	this->contenido->recuperar();
	return "carpetaRecuperada";
}

// ------ METODOS DE CARPETA ------- //
void Carpeta::setNombre(std::string nombre)
{
	this->carpetaLogica->setNombre(nombre);
	this->contenido->setNombre(nombre);
}
//void Carpeta::setEtiqueta(std::string etiqueta)
//{
//	this->carpetaLogica->setEtiqueta(etiqueta);
//}
void Carpeta::agregarEtiqueta(std::string etiqueta)
{
	this->carpetaLogica->agregarEtiqueta(etiqueta);
}
void Carpeta::setUltimaFechaModif(std::string ultimaFechaModif)
{
	this->carpetaLogica->setUltimaFechaModif(ultimaFechaModif);
}
void Carpeta::setUltimoUsuarioModif(std::string ultimoUsuarioModif)
{
	this->carpetaLogica->setUltimoUsuarioModif(ultimoUsuarioModif);
}
void Carpeta::setPropietario(std::string propietario)
{
	this->carpetaLogica->setPropietario(propietario);
}
void Carpeta::setBajaLogica(std::string bajaLogica)
{
	this->carpetaLogica->setBajaLogica(bajaLogica);
}
void Carpeta::setDireccion(std::string direccion)
{
	this->carpetaLogica->setDireccion(direccion);
	this->contenido->setDireccion(direccion);
}

std::string Carpeta::getNombre()
{
	return this->carpetaLogica->getNombre();
}
//std::string Carpeta::getEtiqueta()
//{
//	return this->carpetaLogica->getEtiqueta();
//}
std::vector<std::string> Carpeta::getEtiquetas()
{
	return this->carpetaLogica->getEtiquetas();
}
std::string Carpeta::getUltimaFechaModif()
{
	return this->carpetaLogica->getUltimaFechaModif();
}
std::string Carpeta::getUltimoUsuarioModif()
{
	return this->carpetaLogica->getUltimoUsuarioModif();
}
std::string Carpeta::getPropietario()
{
	return this->carpetaLogica->getPropietario();
}
std::string Carpeta::getBajaLogica()
{
	return this->carpetaLogica->getBajaLogica();
}
std::string Carpeta::getDireccion()
{
	return this->carpetaLogica->getDireccion();
}

std::string Carpeta::getPath()
{
	return this->carpetaLogica->getPath();
}

bool Carpeta::existeFisicamente()
{
	ManagerArchivos manager;
	return manager.existe( this->getPath() );
}
bool Carpeta::estaVacia()
{
	ManagerArchivos manager;
	return manager.carpetaEstaVacia( this->getPath() );
}

// Metodos de EntidadBD
void Carpeta::setContenido(std::string contenido)
{
	this->carpetaLogica->setContenido( contenido );
}
std::string Carpeta::getValor()
{
	return this->carpetaLogica->getContenido();
}
std::string Carpeta::getColumnaDeFamilia()
{
	return "no-column";
}
std::string Carpeta::getClave()
{
	return this->carpetaLogica->getPath();
}
