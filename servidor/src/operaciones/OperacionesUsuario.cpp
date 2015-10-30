/*
 * OperacionesUsuario.cpp
 *
 *  Created on: 28/10/2015
 *      Author: manuel
 */

#include "OperacionesUsuario.h"

using namespace ConexionServidor::Operaciones;

OperacionesUsuario::OperacionesUsuario() {}

OperacionesUsuario::~OperacionesUsuario() {}

void OperacionesUsuario::delet(std::string contenido)
{
	std::cout << "OperacionesUsuario->delete" << "\n";
}
void OperacionesUsuario::get(std::string contenido)
{
	std::cout << "OperacionesUsuario->get" << "\n";
}
void OperacionesUsuario::post(std::string contenido)
{
	std::cout << "OperacionesUsuario->post" << "\n";
}
void OperacionesUsuario::put(std::string contenido)
{
	std::cout << "OperacionesUsuario->put" << "\n";
}

std::string OperacionesUsuario::impresion()
{

}
