

#ifndef ACCIONES_H_
#define ACCIONES_H_

// base de datos
#include "../archivos/Archivo.h"
// entidades
#include "../bd/entidades/ArchivoLogico.h"
#include "../bd/entidades/ContenidoPorCarpeta.h"
#include "../bd/entidades/VersionDeArchivoPorUsuario.h"
#include "../bd/entidades/CarpetaLogica.h"
#include "../bd/entidades/User.h"
// Operaciones
#include "InfoOperaciones.h"

// STL
#include <algorithm>
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{

class Acciones
{
public:
	Acciones();
	virtual ~Acciones();

	// basicos
	bool darDeAltaArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool darDeAltaArchivoFisico(ConexionServidor::BaseDeDatos::Archivo*);
	bool darDeBajaArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool agregarArchivoLogicoAContenido(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	bool agregarCarpetaLogicaAContenido(ConexionServidor::BaseDeDatos::CarpetaLogica* carpetaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	bool sacarArchivoLogicoDeContenido(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	bool sacarCarpetaLogicaDeContenido(ConexionServidor::BaseDeDatos::CarpetaLogica* carpetaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	bool modificarArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool modificarArchivoFisico(ConexionServidor::BaseDeDatos::Archivo*);
	// complejos
	bool agregarArchivoLogicoASuCarpetaLogica(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool sacarArchivoLogicoDeSuCarpetaLogica(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool agregarArchivoLogicoAPapelera(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool existeArchivoLogicoEnContenidoDeCarpeta(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	bool existeCarpetaLogicaEnContenidoDeCarpeta(ConexionServidor::BaseDeDatos::CarpetaLogica* carpetaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	bool agregarArchivoALaListaDeArchivosDeUsuario(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico );
	bool crearVersionInicialDeArchivo(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool versionDeUltimoModificadorEstaActualizada(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool actualizarVersionDeUltimoModificador(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	bool actualizarVersionDelQueDescarga(ConexionServidor::BaseDeDatos::ArchivoLogico*, ConexionServidor::BaseDeDatos::User* );

	ConexionServidor::BaseDeDatos::ArchivoLogico* parsearArchivoDeQuery( std::string query );

	std::string nombreClase();
};
};
};

#endif /* ACCIONES_H_ */
