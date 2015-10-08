/*
 * GET.cpp
 *
 *  Created on: 27/9/2015
 *      Author: manuel
 */

#include "GET.h"

using namespace ConexionServidor::Request;
using namespace std;

GET::GET() {}

GET::~GET() {}

void GET::ejecutar(std::string entidad, std::string contenido)
{
	cout << "GET {entidad:"<<entidad << " contenido: " <<contenido << "}" << endl;
}

std::string GET::impresion()
{
	return std::string("GET");
}
