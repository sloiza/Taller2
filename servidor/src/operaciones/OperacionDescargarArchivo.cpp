

#include "OperacionDescargarArchivo.h"

using namespace ConexionServidor::Operaciones;

OperacionDescargarArchivo::OperacionDescargarArchivo() {}

OperacionDescargarArchivo::~OperacionDescargarArchivo() {}

ConexionServidor::Respuesta OperacionDescargarArchivo::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionDescargarArchivo::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::Archivo archivoFisico( contenido->getStringDeBytes() );

	ConexionServidor::Respuesta respuesta;
	if ( archivoFisico.existeFisicamente() == false)
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("Archivo a descargar inexistente.");
		return respuesta;
	}

	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico = new ConexionServidor::BaseDeDatos::ArchivoLogico( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::User* usuarioQueDescarga = new ConexionServidor::BaseDeDatos::User( contenido->getStringDeBytes() );
	if ( this->acciones.actualizarVersionDelQueDescarga( archivoLogico, usuarioQueDescarga ) == false )
	{
		respuesta.setEstado("error");
		respuesta.setMensaje("Error al realizar la descarga.");
		return respuesta;
	}

// INICIO ------ CODIGO QUE USO SI DEVUELVO EL ARCHIVO CON mg_send_file -------- //
//	respuesta.setEstado("ok");
//	respuesta.setMensaje("Archivo descargado correctamente!");
//	respuesta.setEsDescarga(true);
//	respuesta.setPathDelArchivoADescargar( archivoFisico.getPath() );
// FIN --------- CODIGO QUE USO SI DEVUELVO EL ARCHIVO CON mg_send_file -------- //

// INICIO ------ CODIGO QUE USO SI DEVUELVO EL ARCHIVO POR JSON -------- //
	archivoFisico.recuperar();
	respuesta.setBytes( archivoFisico.getBytes()->getBytesBase64() );

	respuesta.setEsDescarga(true);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Archivo descargado correctamente!");
// FIN --------- CODIGO QUE USO SI DEVUELVO EL ARCHIVO POR JSON -------- //

	delete archivoLogico;
	delete usuarioQueDescarga;

	return respuesta;
}
ConexionServidor::Respuesta OperacionDescargarArchivo::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionDescargarArchivo::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}

void OperacionDescargarArchivo::imprimir()
{
	std::cout << "descargar\n";
}
