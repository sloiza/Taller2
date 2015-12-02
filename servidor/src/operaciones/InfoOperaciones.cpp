

#include "InfoOperaciones.h"

using namespace ConexionServidor::Operaciones;

const std::string InfoOperaciones::nombresRecursos[] = { "principal", "usuario", "archivos", "carpetas", "compartirArchivo", "compartirCarpeta", "descargar", "papelera", "buscar" };

const std::string InfoOperaciones::carpetaRaiz = "archivos/";

const std::string InfoOperaciones::compartidos = "compartido";

const std::string InfoOperaciones::papelera = "papelera";

const std::string InfoOperaciones::carpetaArchivosPorUsuario = "totalArchivos";

InfoOperaciones::InfoOperaciones() {}

InfoOperaciones::~InfoOperaciones() {}

