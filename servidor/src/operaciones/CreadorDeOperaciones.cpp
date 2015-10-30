/*
 * CreadorDeOperaciones.cpp
 *
 *  Created on: 29/10/2015
 *      Author: manuel
 */

#include "CreadorDeOperaciones.h"

using namespace ConexionServidor::Operaciones;

std::vector<std::string> CreadorDeOperaciones::campos(0);
Recurso* CreadorDeOperaciones::raiz = NULL;

CreadorDeOperaciones::CreadorDeOperaciones()
{
	crearArbolDeRecursos();
}

CreadorDeOperaciones::~CreadorDeOperaciones()
{
	liberarArbolDeRecursos();
}

void CreadorDeOperaciones::crearArbolDeRecursos()
{
	Recurso* principal = new Recurso();
	principal->nombre = "principal";
	//principal->operacion = new OperacionPrincipal();

	Recurso* usuarios = new Recurso();
	usuarios->nombre = "usuario";
	usuarios->operacion = new OperacionesUsuario();

	Recurso* perfil = new Recurso();
	perfil->nombre = "miPerfil";
	//perifl->operacion = new OperacionPerfil();

	Recurso* baul = new Recurso();
	baul->nombre = "miBaul";
	baul->operacion = new OperacionesArchivos();

	Recurso* carpetas = new Recurso();
	carpetas->nombre = "misCarpetas";
	//archivos->operacion = new OperacionesCarpetas();

	Recurso* compartirArchivo = new Recurso();
	compartirArchivo->nombre = "compartirArchivo";
	//compartirArchivo->operacion = new OperacionCompartirArchivo();

	Recurso* compartirCarpeta = new Recurso();
	compartirCarpeta->nombre = "compartirCarpeta";
	//compartirCarpeta->operacion = new OperacionCompartirCarpeta();

	Recurso* descargarArchivo = new Recurso();
	descargarArchivo->nombre = "descargar";
	//descargarArchivo->operacion = new OperacionDescargarArchivo();

	principal->hijos.push_back(usuarios);
	usuarios->hijos.push_back(baul);
	usuarios->hijos.push_back(perfil);
	baul->hijos.push_back(carpetas);
	baul->hijos.push_back(compartirArchivo);
	baul->hijos.push_back(compartirCarpeta);
	baul->hijos.push_back(descargarArchivo);

	raiz = usuarios;
}

void CreadorDeOperaciones::liberarArbolDeRecursos()
{
	liberarRecusivamente(raiz);
}

void CreadorDeOperaciones::dividirRecursos(std::string uri)
{
	campos.clear();

	if ( uri == "" )
	{
		return;
	}

    std::istringstream streamUri(uri);
    std::string campo;
    while (std::getline(streamUri, campo, '/'))
    {
        campos.push_back(campo);
    }
    if ( campos.back().find('?') == std::string::npos )
    {// si no hay query entonces ya termine.
    	return;
    }

    std::string ultimoRecursoYQuery = campos.back();
    campos.pop_back();

    std::istringstream streamUltimoRecursoYQuery(ultimoRecursoYQuery);
    std::string ultimaRecurso;
    std::string query;
    std::getline(streamUltimoRecursoYQuery, ultimaRecurso, '?');
    std::getline(streamUltimoRecursoYQuery, query, '?');

    campos.push_back(ultimaRecurso);

    std::istringstream streamQuery(query);
    std::string parametroQuery;
    std::getline(streamQuery, parametroQuery, '=');

    campos.push_back(parametroQuery);
}

std::vector<std::string> CreadorDeOperaciones::getCampos()
{
	return campos;
}

IOperable* CreadorDeOperaciones::getOperacion(ConexionServidor::Request::URI* uri)
{
    campos = uri->getRecursosDividos();

    return reconocerUriRecursivamente(raiz, 0);
}

IOperable* CreadorDeOperaciones::reconocerUriRecursivamente(Recurso* recurso, int nivel)
{
    if ( campos.size() == nivel )
    {
    	return recurso->operacion;
    }

	for ( std::vector<Recurso*>::iterator hijo = recurso->hijos.begin(); hijo != recurso->hijos.end(); hijo++)
	{
		if ( (*hijo)->nombre == campos[nivel] )
		{
			nivel++;
			return reconocerUriRecursivamente(*hijo, nivel);
		}
	}

	return new OperacionErrorURL();
}

void CreadorDeOperaciones::liberarRecusivamente(Recurso* recurso)
{
	if ( recurso == NULL )
	{
		return;
	}

	for ( std::vector<Recurso*>::iterator hijo = recurso->hijos.begin(); hijo != recurso->hijos.end(); hijo++)
	{
		liberarRecusivamente(*hijo);
		if ( *hijo != NULL )
		{
			delete (*hijo)->operacion;
			(*hijo)->operacion = NULL;
			delete *hijo;
			(*hijo) = NULL;
		}
	}
}

