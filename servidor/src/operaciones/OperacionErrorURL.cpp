/*
 * OperacionErrorURL.cpp
 *
 *  Created on: 29/10/2015
 *      Author: manuel
 */

#include "OperacionErrorURL.h"

using namespace ConexionServidor::Operaciones;

OperacionErrorURL::OperacionErrorURL() {}

OperacionErrorURL::~OperacionErrorURL() {}

void OperacionErrorURL::delet(std::string contenido)
{
	std::cout << "OperacionErrorURL->delete" << "\n";
}
void OperacionErrorURL::get(std::string contenido)
{
	std::cout << "OperacionErrorURL->get" << "\n";
}
void OperacionErrorURL::post(std::string contenido)
{
	std::cout << "OperacionErrorURL->post" << "\n";
}
void OperacionErrorURL::put(std::string contenido)
{
	std::cout << "OperacionErrorURL->put" << "\n";
}

std::string OperacionErrorURL::impresion()
{

}
