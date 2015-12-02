/// \file Acciones.h
/// \date 2015-11-26
/// \brief Funciones que realizan acciones logicas y fisicas utilizadas por las operaciones.
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
// utiles
#include "../utiles/base64.h"


// STL
#include <algorithm>
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Funciones que realizan acciones logicas y fisicas utilizadas por las operaciones.
class Acciones
{
public:
	/// \brief Constructor.
	Acciones();
	/// \brief Destructor.
	virtual ~Acciones();

	// basicos
	/// \brief Da de alta el archivo logico.
	bool darDeAltaArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Da de alta el archivo fisico.
	bool darDeAltaArchivoFisico(ConexionServidor::BaseDeDatos::Archivo*);
	/// \brief Da de baja el archivo logico.
	bool darDeBajaArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Agrega archivo logico a contenido logico de carpeta.
	bool agregarArchivoLogicoAContenido(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	/// \brief Agrega carpeta logica a contenido logico de carpeta.
	bool agregarCarpetaLogicaAContenido(ConexionServidor::BaseDeDatos::CarpetaLogica* carpetaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	/// \brief Elimina archivo logico de contenido logico de carpeta.
	bool sacarArchivoLogicoDeContenido(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	/// \brief Elimina carpeta logica de contenido logico de carpeta.
	bool sacarCarpetaLogicaDeContenido(ConexionServidor::BaseDeDatos::CarpetaLogica* carpetaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	/// \brief Modifica archivo logico.
	bool modificarArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Modifica archivo fisico.
	bool modificarArchivoFisico(ConexionServidor::BaseDeDatos::Archivo*);
	// complejos
	/// \brief Agrega archivo logico a su carpeta.
	bool agregarArchivoLogicoASuCarpetaLogica(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Elimina archivo logico de su carpeta.
	bool sacarArchivoLogicoDeSuCarpetaLogica(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Agrega archivo logico a la papelera de usuario.
	bool agregarArchivoLogicoAPapelera(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Chequea si existe archivo logico en contenido.
	bool existeArchivoLogicoEnContenidoDeCarpeta(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	/// \brief Chequea si existe carpeta logica en contenido.
	bool existeCarpetaLogicaEnContenidoDeCarpeta(ConexionServidor::BaseDeDatos::CarpetaLogica* carpetaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido );
	/// \brief Agrega archivo a la lista de archivos del usuario.
	bool agregarArchivoALaListaDeArchivosDeUsuario(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico );
	/// \brief Crea version inicial del archivo para su usuario.
	bool crearVersionInicialDeArchivo(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Chequea si la version del usuario esta actualizada.
	bool versionDeUltimoModificadorEstaActualizada(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Actualiza la version del ultimo modificador.
	bool actualizarVersionDeUltimoModificador(ConexionServidor::BaseDeDatos::ArchivoLogico*);
	/// \brief Actualiza la version del que realiza la descarga.
	bool actualizarVersionDelQueDescarga(ConexionServidor::BaseDeDatos::ArchivoLogico*, ConexionServidor::BaseDeDatos::User* );

	/// \brief Parsea la query con los datos logicos del archivo y devuelve el archivo logico.
	ConexionServidor::BaseDeDatos::ArchivoLogico* parsearArchivoDeQuery( std::string query );

	/// \brief Devuelve nombre de la clase.
	std::string nombreClase();

	//std::vector<std::string> obtenerEtiquetas(std::string etiquetasEncodeadas);
};
};
};

#endif /* ACCIONES_H_ */
