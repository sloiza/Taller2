/*
 * URI.cpp
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#include "URI.h"

using namespace ConexionServidor::Request;

URI::URI() {}

URI::URI(std::string uri)
{
	this->uri = uri;
}

URI::~URI() {}

ConexionServidor::BaseDeDatos::EntidadDB* URI::getEntidadAManejar()
{
	//return this->uri;
}

std::string URI::getURI()
{
	return this->uri;
}

void URI::setURI(std::string uri)
{
	this->uri = uri;
}

std::vector<std::string> URI::getRecursosDividos()
{
	if ( uri == "" )
	{
		return std::vector<std::string>(0);
	}

	std::vector<std::string> campos;
    std::istringstream streamUri(uri);
    std::string campo;
    while (std::getline(streamUri, campo, '/'))
    {
        //std::cout << campo << std::endl;
        campos.push_back(campo);
    }
    if ( campos.back().find('?') == std::string::npos )
    {// si no hay query entonces ya termine.
    	return campos;
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

    return campos;
}
