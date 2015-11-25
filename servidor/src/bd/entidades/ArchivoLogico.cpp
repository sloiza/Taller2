/*
 * Archivo.cpp
 *
 *  Created on: 25/10/2015
 *      Author: manuel
 */

#include "ArchivoLogico.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string ArchivoLogico::etiquetas[] = {"nombre", "extension", "etiqueta", "fecha_ulti_modi", "usuario_ulti_modi", "propietario", "baja_logica", "direccion", "compartido_con" , "version" };

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
//void ArchivoLogico::setEtiqueta(std::string etiqueta)
//{
//	this->info->setAtributo(etiquetas[ETIQUETA], etiqueta);
//}
void ArchivoLogico::agregarEtiqueta(std::string etiqueta)
{
	this->info->agregarValorAAtributo(etiquetas[ETIQUETA], etiqueta);
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
void ArchivoLogico::setDireccion(std::string direccion)
{
	this->info->setAtributo(etiquetas[DIRECCION], direccion);
}
void ArchivoLogico::setVersion(std::string version)
{
	this->info->setAtributo(etiquetas[VERSION], version);
}
void ArchivoLogico::setPath(std::string path)
{
	std::vector<std::string> campos = Utiles::Metodos::split(path , '/');

	int tamanio = campos.size();

	std::string direccion = "";
	std::string nombre = "";
	std::string extension = "";

	if ( campos[0].compare("") == 0 )
	{// si el primer campo es vacio, entonces quiere decir q la direccion es vacia.
		this->setDireccion("");
	}
	else
	{
		for ( int i = 0; i < tamanio-1 ;  i++)
		{
			direccion += campos[i] + "/";
		}
		this->setDireccion(direccion);
	}


	std::vector<std::string> nombreYExtension = Utiles::Metodos::split(campos[campos.size()-1], '.');

	if ( nombreYExtension.size() == 1 )
	{// si el vector "nombreYExtension" tiene tamanio 1, entonces no hay extension.
		this->setNombre( nombreYExtension[0] );
		this->setExtension( "" );
		return;
	}

	int i;
	int tamanioNombre = nombreYExtension.size();
	for ( i = 0; i < tamanioNombre-2 ;  i++)
	{
		nombre += nombreYExtension[i] + ".";
	}
	nombre += nombreYExtension[i];
	this->setNombre(nombre);

	this->setExtension(nombreYExtension[tamanioNombre-1]);
}
void ArchivoLogico::agregarCompartidoCon(std::string usuario)
{
	this->info->agregarValorAAtributo(etiquetas[COMPARTIDO_CON], usuario);
}

std::string ArchivoLogico::getNombre()
{
	return this->info->getAtributo(etiquetas[NOMBRE], "nombreDefault");
}
std::string ArchivoLogico::getExtension()
{
	return this->info->getAtributo(etiquetas[EXTENSION], "extensionDefault");
}
//std::string ArchivoLogico::getEtiqueta()
//{
//	return this->info->getAtributo(etiquetas[ETIQUETA], "etiquetaDefault");
//}
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
std::string ArchivoLogico::getDireccion()
{
	return this->info->getAtributo(etiquetas[DIRECCION], "direccionDefault");
}
std::string ArchivoLogico::getVersion()
{
	return this->info->getAtributo(etiquetas[VERSION], "versionDefault");
}

std::string ArchivoLogico::getNombreYExtension()
{
	return this->getNombre() + "." + this->getExtension();
}
std::string ArchivoLogico::getPath()
{
	return this->getDireccion() + this->getNombre() + "." + this->getExtension();
}

std::vector<std::string> ArchivoLogico::getEtiquetas()
{
	return this->info->getListaDeValorDeAtributo(etiquetas[ETIQUETA], "etiquetaDefault");
}
std::vector<std::string> ArchivoLogico::getCompartidoCon()
{
	return this->info->getListaDeValorDeAtributo(etiquetas[COMPARTIDO_CON], "compartidosConDefault");
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
	return this->getPath();
}


