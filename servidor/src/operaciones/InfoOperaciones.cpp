/*
 * InfoOperaciones.cpp
 *
 *  Created on: 31/10/2015
 *      Author: manuel
 */

#include "InfoOperaciones.h"

using namespace ConexionServidor::Operaciones;

const std::string InfoOperaciones::nombresRecursos[] = { "principal", "usuario", "archivos", "carpetas", "compartirArchivo", "compartirCarpeta", "descargar", "papelera" };

const std::string InfoOperaciones::carpetaRaiz = "tmp/";

const std::string InfoOperaciones::compartidos = "compartido";

const std::string InfoOperaciones::papelera = "papelera";

const std::string InfoOperaciones::carpetaArchivosPorUsuario = "totalArchivos";

InfoOperaciones::InfoOperaciones() {}

InfoOperaciones::~InfoOperaciones() {}

