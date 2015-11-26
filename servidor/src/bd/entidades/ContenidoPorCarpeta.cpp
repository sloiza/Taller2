
#include "ContenidoPorCarpeta.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string ContenidoPorCarpeta::etiquetas[] = {"nombre", "direccion", "archivos", "carpetas" };

ContenidoPorCarpeta::ContenidoPorCarpeta() {}

ContenidoPorCarpeta::ContenidoPorCarpeta(std::string contenido)
{
	this->info->setContenido(contenido);
}

ContenidoPorCarpeta::~ContenidoPorCarpeta() {}

void ContenidoPorCarpeta::setPath(std::string path)
{
	std::vector<std::string> campos = Utiles::Metodos::split(path , '/');

	int tamanio = campos.size();

	if ( campos[tamanio-1].compare("") == 0 )
	{// si el ultimo campo es vacio, entonces quiere decir q el path me llego con una '/' al final.
	 //	entonces le resto 1 a 'tamanio' para no tener esa barra en cuenta.
		tamanio--;
	}

	if ( tamanio == 1 )
	{ // si el tamanio q me qeda es 1, entonces solo tengo el nombre de la carpeta, en la direccion raiz.
		this->setNombre( campos[0] );
		this->setDireccion("/");
		return;
	}

	std::string direccion = "";
	for ( int i = 0; i < tamanio-1 ;  i++)
	{
		direccion += campos[i] + "/";
	}

	std::string nombre = campos[tamanio-1];

	this->setNombre( nombre );
	this->setDireccion( direccion );
}
void ContenidoPorCarpeta::setNombre(std::string nombre)
{
	this->info->setAtributo(etiquetas[NOMBRE], nombre);
}
void ContenidoPorCarpeta::setDireccion(std::string direccion)
{
	this->info->setAtributo(etiquetas[DIRECCION], direccion);
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
void ContenidoPorCarpeta::eliminarTodosLosArchivos()
{
	this->info->borrarValoresDeAtributo(etiquetas[ARCHIVOS]);
}
void ContenidoPorCarpeta::eliminarTodasLosCarpetas()
{
	this->info->borrarValoresDeAtributo(etiquetas[CARPETAS]);
}

std::string ContenidoPorCarpeta::getPath()
{
	return this->getDireccion() + this->getNombre();
}
std::string ContenidoPorCarpeta::getNombre()
{
	return this->info->getAtributo(etiquetas[NOMBRE], "nombreDefault");
}
std::string ContenidoPorCarpeta::getDireccion()
{
	return this->info->getAtributo(etiquetas[DIRECCION], "direccionDefault");
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
