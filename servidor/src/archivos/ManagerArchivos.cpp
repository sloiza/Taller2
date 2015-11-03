/*
 * ManagerArchivos.cpp
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#include "ManagerArchivos.h"

using namespace ConexionServidor::BaseDeDatos;

ManagerArchivos::ManagerArchivos() {}

ManagerArchivos::~ManagerArchivos() {}

void ManagerArchivos::escribir(std::string path, Utiles::Bytes* bytes)
{
	std::ofstream escritor(path.c_str(), std::ios::out | std::ios::app | std::ios::binary);

	if ( escritor.is_open() )
	{
		escritor.write(bytes->getBytes(), bytes->getTamanio());
		escritor.flush();
		escritor.close();
		Utiles::Log::instancia()->info("Archivo guardado: " + path, "ManagerArchivos");
	}
	else
	{
		Utiles::Log::instancia()->info("No pudo abrir el archivo para escritura: " + path, "ManagerArchivos");
	}
}
void ManagerArchivos::eliminar(std::string path)
{
	struct stat buffer;
	if (stat(path.c_str(), &buffer) == 0)
	{
		std::remove(path.c_str());
	}
}
Utiles::Bytes* ManagerArchivos::leer(std::string path)
{
	int tamanioArchivo = 0;
	char* bloqueDeBytes = NULL;

	std::ifstream lector(path.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	if ( lector.is_open() )
	{
		tamanioArchivo = lector.tellg();
		bloqueDeBytes = new char [tamanioArchivo];
		lector.seekg(0, std::ios::beg);
		lector.read(bloqueDeBytes, tamanioArchivo);
	    lector.close();
	}
	else
	{
		Utiles::Log::instancia()->info("No pudo abrir el archivo para lectura: " + path, "ManagerArchivos");
		if ( bloqueDeBytes != NULL )
		{
			delete[] bloqueDeBytes;
			bloqueDeBytes = NULL;
		}
		return NULL;
	}

	Utiles::Bytes* bytes = new Utiles::Bytes(bloqueDeBytes, tamanioArchivo);
	Utiles::Log::instancia()->info("Archivo leido: " + path, "ManagerArchivos");
	return bytes;
}

void ManagerArchivos::modificar(std::string path, Utiles::Bytes* bytes)
{
	this->eliminar(path);
	this->escribir(path, bytes);
}

bool ManagerArchivos::existe(std::string path)
{
	struct stat buffer;
	if (stat(path.c_str(), &buffer) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
