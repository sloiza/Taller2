

#include "OperacionPrincipal.h"

using namespace ConexionServidor::Operaciones;

OperacionPrincipal::OperacionPrincipal() {}

OperacionPrincipal::~OperacionPrincipal() {}

ConexionServidor::Respuesta OperacionPrincipal::delet(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionPrincipal::get(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::BaseDeDatos::User usuario( contenido->getStringDeBytes() );
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoDeCarpeta;

	contenidoDeCarpeta.setPath( InfoOperaciones::carpetaRaiz + usuario.getEmail() );

	Utiles::Log::instancia()->debug("accedido a contenido principal: '" + contenidoDeCarpeta.getPath() + "'.", "OperacinPrincipal");

	std::string valorRecuperado = contenidoDeCarpeta.recuperar();

	ConexionServidor::Respuesta respuesta;
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		respuesta.setEstado("no-existe");
		respuesta.setMensaje("No existe carpeta para el usuario inexistente.");
		return respuesta;
	}

	respuesta.setContenido(valorRecuperado);
	respuesta.setEstado("ok");
	respuesta.setMensaje("Pagina principal accedida correctamente!");
	return respuesta;

}
ConexionServidor::Respuesta OperacionPrincipal::post(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}
ConexionServidor::Respuesta OperacionPrincipal::put(Utiles::Bytes* contenido, std::string query)
{
	ConexionServidor::Respuesta respuesta;
	respuesta.setEstado("error");
	respuesta.setMensaje("operacion no implementada.");
	return respuesta;
}

void OperacionPrincipal::imprimir()
{
	std::cout << "principal\n";
}
