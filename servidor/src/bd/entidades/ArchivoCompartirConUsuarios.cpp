

#include "ArchivoCompartirConUsuarios.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string ArchivoCompartirConUsuarios::etiquetas[] = { "nombre", "direccion", "extension", "usuarios" };

ArchivoCompartirConUsuarios::ArchivoCompartirConUsuarios() {}

ArchivoCompartirConUsuarios::ArchivoCompartirConUsuarios(std::string contenido)
{
	this->info->setContenido( contenido );
}

ArchivoCompartirConUsuarios::~ArchivoCompartirConUsuarios() {}

std::string ArchivoCompartirConUsuarios::getNombreArchivo()
{
	return this->info->getAtributo(etiquetas[NOMBRE], "nombreDefault");
}
std::string ArchivoCompartirConUsuarios::getDireccionArchivo()
{
	return this->info->getAtributo(etiquetas[DIRECCION], "direccionDefault");
}
std::string ArchivoCompartirConUsuarios::getExtensionArchivo()
{
	return this->info->getAtributo(etiquetas[EXTENSION], "extensionDefault");
}
std::string ArchivoCompartirConUsuarios::getPathArchivo()
{
	return this->getDireccionArchivo() + this->getNombreArchivo() + "." + this->getExtensionArchivo();
}
std::vector<std::string> ArchivoCompartirConUsuarios::getUsuariosACompartirles()
{
	return this->info->getListaDeValorDeAtributo(etiquetas[USUARIOS], "usuariosDefault");
}

// Metodos de EntidadDB
std::string ArchivoCompartirConUsuarios::getValor()
{
	return this->info->getContenido();
}

std::string ArchivoCompartirConUsuarios::getColumnaDeFamilia()
{
	return "file";
}

std::string ArchivoCompartirConUsuarios::getClave()
{
	//return "contenido" + this->getPath();
	return "noImportaPorqNuncaSeAlmacena";
}
