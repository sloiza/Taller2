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

void ManagerArchivos::crearCarpeta(std::string direccion, std::string nombre)
{
	std::string path = direccion + nombre;
	mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
}
void ManagerArchivos::crearCarpeta(std::string path)
{
	mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR);
}

void ManagerArchivos::eliminarCarpetaVacia(std::string direccion, std::string nombre)
{
	std::string path = direccion + nombre;
	rmdir( path.c_str() );
	//delete_folder_tree( path.c_str() );
}
void ManagerArchivos::eliminarCarpetaVacia(std::string path)
{
	rmdir( path.c_str() );
	//delete_folder_tree( path.c_str() );
}


bool ManagerArchivos::pathEsCarpeta(std::string path)
{
	return this->path_is_directory( path.c_str() );
}

bool ManagerArchivos::carpetaEstaVacia(std::string path)
{

	DIR*            dp = opendir(path.c_str());
	struct dirent*  ep = readdir(dp);
	struct dirent*  entry = readdir(dp);
	readdir_r(dp, entry, &ep);
	if ( ep == NULL ) // si el nombre del directorio es ".", entonces no tiene archivos.
	{
		closedir(dp);
		return true;
	}
	else
	{
		closedir(dp);
		return false;
	}
}

void ManagerArchivos::delete_folder_tree (const char* directory_name)
{
    DIR*            dp;
    struct dirent*  ep;
    char            p_buf[512] = {0};

    dp = opendir(directory_name);

    while ((ep = readdir(dp)) != NULL) {
        sprintf(p_buf, "%s/%s", directory_name, ep->d_name);
        if (path_is_directory(p_buf))
            this->delete_folder_tree(p_buf);
        else
            unlink(p_buf);
    }

    closedir(dp);
    rmdir(directory_name);
}

int ManagerArchivos::path_is_directory (const char* path) {
    struct stat s_buf;

    if (stat(path, &s_buf))
        return 0;

    return S_ISDIR(s_buf.st_mode);
}
