
#include "OperacionesPapelera.h"

using namespace ConexionServidor::Operaciones;

OperacionesPapelera::OperacionesPapelera() {}

OperacionesPapelera::~OperacionesPapelera() {}

ConexionServidor::Respuesta OperacionesPapelera::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::User usuarioAux( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( usuarioAux.getEmail() + "/" + InfoOperaciones::papelera );
	std::string valorRecuperadoPapelera = papelera.recuperar();

	ConexionServidor::Respuesta respuesta;
	if ( valorRecuperadoPapelera.compare("vacio") != 0 )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("No existe papelera para el usuario.");
		return respuesta;
	}

	papelera.setContenido( valorRecuperadoPapelera );
	papelera.eliminarTodosLosArchivos();
	papelera.modificar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Papelera vaciada correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesPapelera::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::User usuarioAux( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( usuarioAux.getEmail() + "/" + InfoOperaciones::papelera );

	std::string valorRecuperado = papelera.recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{
		papelera.setContenido( valorRecuperado );
	}

	ConexionServidor::Respuesta respuesta;
	respuesta.setContenido(valorRecuperado);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Papelera accedida correctamente!");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesPapelera::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionesPapelera::put(Utiles::Bytes* contenido, std::string query)
{
	// NOTA: SI SE LLAMA A "PUT /papelera + datos.json" el archivo se restaurara, aun aunq no este en la papelera.
	// se supone que siempre "datos.json" siempre tendran datos de un archivo ubicado en la papelera.

	ConexionServidor::BaseDeDatos::User usuarioAux( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ArchivoLogico archivoARecuperar( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	ConexionServidor::Respuesta respuesta;
	// si el json llega sin extension, entonces quiere decir q se quiere recuperar una carpeta.
	if ( archivoARecuperar.getExtension().compare("extensionDefault") == 0 )
	{
		if ( restaurarCarpeta(contenido, usuarioAux.getEmail() ) )
		{
			respuesta.setEstado("ok");
			respuesta.setMensaje("Carpeta restaurada correctamente!");
		}
		else
		{
			respuesta.setEstado("error");
			respuesta.setMensaje("Error al restaurar carpeta.");
		}
		return respuesta;
	}

	papelera.setPath( usuarioAux.getEmail() + "/" + InfoOperaciones::papelera );

	this->acciones.sacarArchivoLogicoDeContenido( &archivoARecuperar, &papelera );

	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta carpetaOriginal;
	carpetaOriginal.setPath( archivoARecuperar.getDireccion() );

	this->acciones.agregarArchivoLogicoAContenido( &archivoARecuperar, &carpetaOriginal );


	std::string valorRecuperadoArchivo = archivoARecuperar.recuperar();
	if ( valorRecuperadoArchivo.compare("vacio") == 0 )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("No existe archivo.");
		return respuesta;
	}

	archivoARecuperar.setContenido( valorRecuperadoArchivo );

	archivoARecuperar.setBajaLogica( "no" );
	archivoARecuperar.modificar();

	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo restaurado correctamente!");
	return respuesta;
}

void OperacionesPapelera::imprimir()
{
	std::cout << "papelera\n";
}

bool OperacionesPapelera::restaurarCarpeta(Utiles::Bytes* contenido, std::string mail)
{
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta carpetaOriginal;
	ConexionServidor::BaseDeDatos::CarpetaLogica carpetaARecuperar( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( mail + "/" + InfoOperaciones::papelera );
	bool resSacar =  this->acciones.sacarCarpetaLogicaDeContenido( &carpetaARecuperar, &papelera );

	std::string valorRecuperadoArchivo = carpetaARecuperar.recuperar();
	if ( valorRecuperadoArchivo.compare("vacio") == 0 )
	{
		return false;
	}

	carpetaARecuperar.setContenido( valorRecuperadoArchivo );

	carpetaARecuperar.setBajaLogica( "no" );
	carpetaARecuperar.modificar();

	carpetaOriginal.setPath( carpetaARecuperar.getDireccion() );
	bool resAgregar =this->acciones.agregarCarpetaLogicaAContenido( &carpetaARecuperar, &carpetaOriginal );

	if ( resSacar && resAgregar )
	{
		return true;
	}
	else
	{
		return false;
	}
}

