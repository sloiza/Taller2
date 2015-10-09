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
