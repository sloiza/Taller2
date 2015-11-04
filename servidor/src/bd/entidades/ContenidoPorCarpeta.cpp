/*
 * ContenidoPorCarpeta.cpp
 *
 *  Created on: 4/11/2015
 *      Author: manuel
 */

#include "ContenidoPorCarpeta.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string ContenidoPorCarpeta::etiquetas[] = {"path", "archivos", "carpetas" };

ContenidoPorCarpeta::ContenidoPorCarpeta() {}

ContenidoPorCarpeta::ContenidoPorCarpeta(std::string contenido)
{
	this->info->setContenido(contenido);
}

ContenidoPorCarpeta::~ContenidoPorCarpeta() {}

void ContenidoPorCarpeta::setPath(std::string path)
{
	this->info->setAtributo(etiquetas[PATH], path);
}
void ContenidoPorCarpeta::agregarArchivo(std::string archivoNuevo)
{
	this->info->agregarValorAAtributo(etiquetas[ARCHIVOS], archivoNuevo);
}
void ContenidoPorCarpeta::agregarCarpeta(std::string carpetaNueva)
{
	this->info->agregarValorAAtributo(etiquetas[CARPETAS], carpetaNueva);
}
void ContenidoPorCarpeta::eliminarArchivo(std::string archivoAEliminar)
{
	this->info->borrarValorDeAtributo(etiquetas[ARCHIVOS], archivoAEliminar);
}
void ContenidoPorCarpeta::eliminarCarpeta(std::string carpetaAEliminar)
{
	this->info->borrarValorDeAtributo(etiquetas[CARPETAS], carpetaAEliminar);
}

std::string ContenidoPorCarpeta::getPath()
{
	return this->info->getAtributo(etiquetas[PATH], "pathDefault");
}
std::vector<std::string> ContenidoPorCarpeta::getArchivos()
{
	return this->info->getListaDeValorDeAtributo(etiquetas[ARCHIVOS], "archivosDefault");
}
std::vector<std::string> ContenidoPorCarpeta::getCarpetas()
{
	return this->info->getListaDeValorDeAtributo(etiquetas[CARPETAS], "carpetasDefault");
}

// Metodos de EntidadDB
std::string ContenidoPorCarpeta::getValor()
{
	return this->info->getContenido();
}

std::string ContenidoPorCarpeta::getColumnaDeFamilia()
{
	return "file";
}

std::string ContenidoPorCarpeta::getClave()
{
	return "contenido" + this->getPath();
}
