/*
 * InfoOperaciones.cpp
 *
 *  Created on: 31/10/2015
 *      Author: manuel
 */

#include "InfoOperaciones.h"

using namespace ConexionServidor::Operaciones;

const std::string InfoOperaciones::nombresRecursos[] = { "principal", "usuario", "archivos", "carpetas", "compartirArchivo", "compartirCarpeta", "descargar" };

const std::string InfoOperaciones::carpetaRaiz = "tmp/";

InfoOperaciones::InfoOperaciones() {}

InfoOperaciones::~InfoOperaciones() {}

