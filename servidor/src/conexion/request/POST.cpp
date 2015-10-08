/*
 * POST.cpp
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#include "POST.h"

using namespace ConexionServidor::Request;
using namespace std;

POST::POST() {}

POST::~POST() {}

void POST::ejecutar(std::string entidad, std::string contenido)
{
	cout << "POST {entidad:"<<entidad << " contenido: " <<contenido << "}" << endl;

}

std::string POST::impresion()
{
	return std::string("POST");
}
