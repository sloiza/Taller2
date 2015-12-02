
#include "Acciones.h"

using namespace ConexionServidor::Operaciones;

Acciones::Acciones() {}

Acciones::~Acciones() {}

// ---------- simples ---------- //
bool Acciones::darDeAltaArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	std::string valorRecuperado = archivoLogico->recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si ya existe un archivo con esos datos devuelvo FALSE.
		Utiles::Log::instancia()->warn("Archivo logico: '" + archivoLogico->getPath() + "' ya existe.", this->nombreClase() + ".darDeAltaArchivoLogico()");
		return false;
	}

	archivoLogico->setVersion("1");
	archivoLogico->guardar();

	return true;
}
bool Acciones::darDeAltaArchivoFisico(ConexionServidor::BaseDeDatos::Archivo* archivo)
{
	if ( archivo->existeFisicamente() )
	{// si ya existe el archivo devuelvo FALSE.
		Utiles::Log::instancia()->warn("Ya existe el archivo fisico: '" + archivo->getPath() + "'.", this->nombreClase() + ".darDeAltaArchivoFisico()");
		return false;
	}

	archivo->guardarFisicamente();

	if ( archivo->existeFisicamente() == false )
	{// si no se guardo el archivo devuelvo FALSE.
		Utiles::Log::instancia()->warn("No se guardo fisicamente el archivo: '" + archivo->getPath() + "'.", this->nombreClase() + ".darDeAltaArchivoFisico()");
		return false;
	}

	return true;
}
bool Acciones::darDeBajaArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	std::string valorRecuperado = archivoLogico->recuperar();

	if ( valorRecuperado.compare("vacio") == 0 )
	{// si no recupere el archivo, entonces no existe.
		Utiles::Log::instancia()->warn("No existe el archivo logico: '" + archivoLogico->getPath() + "'.", this->nombreClase() + ".darDeBajaArchivoLogico()");
		return false;
	}

	archivoLogico->setContenido( valorRecuperado );

	if ( archivoLogico->getBajaLogica().compare("si") == 0 )
	{// si ya fue dado de baja logica, devuelvo FALSE.
		Utiles::Log::instancia()->warn("Ya habia sido dado de baja el archivo logico: '" + archivoLogico->getPath() + "'.", this->nombreClase() + ".darDeBajaArchivoLogico()");
		return false;
	}

	archivoLogico->setBajaLogica("si");
	//archivoLogico->guardar();
	archivoLogico->modificar();

	return true;
}
bool Acciones::agregarArchivoLogicoAContenido(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido )
{
	std::string valorRecuperado = contenido->recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si recupero algo, entonces lo seteo el contenido recuperado. sino no hace falta.
		contenido->setContenido(valorRecuperado);
	}
	else
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta: '" + contenido->getPath() + "' no existe.", this->nombreClase() + ".agregarArchivoLogicoAContenido()");
		return false;
	}

	if ( this->existeArchivoLogicoEnContenidoDeCarpeta(archivoLogico, contenido) )
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta '"+ contenido->getPath() +"' ya contiene al archivo logico '" + archivoLogico->getPath() + "'.", this->nombreClase() + ".agregarArchivoLogicoAContenido()");
		return false;
	}

	contenido->agregarArchivo( archivoLogico->getPath() );
	//contenido->guardar();
	contenido->modificar();

	Utiles::Log::instancia()->debug( "'" + archivoLogico->getPath() + "' agregado a ContenidoEnCarpeta: '" + contenido->getPath() +"'.", this->nombreClase() + ".agregarArchivoLogicoAContenido()");

	return true;
}
bool Acciones::agregarCarpetaLogicaAContenido(ConexionServidor::BaseDeDatos::CarpetaLogica* careptaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido )
{
	std::string valorRecuperado = contenido->recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si recupero algo, entonces lo seteo el contenido recuperado. sino no hace falta.
		contenido->setContenido(valorRecuperado);
	}
	else
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta: '" + contenido->getPath() + "' no existe.", this->nombreClase() + ".agregarCarpetaLogicaAContenido()");
		return false;
	}

	if ( this->existeCarpetaLogicaEnContenidoDeCarpeta(careptaLogica, contenido) )
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta '"+ contenido->getPath() +"' ya contiene la carpeta logica '" + careptaLogica->getPath() + "'.", this->nombreClase() + ".agregarCarpetaLogicaAContenido()");
		return false;
	}

	contenido->agregarCarpeta( careptaLogica->getPath() );
	//contenido->guardar();
	contenido->modificar();

	return true;
}
bool Acciones::sacarArchivoLogicoDeContenido(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido )
{
	std::string valorRecuperado = contenido->recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si recupero algo, entonces lo seteo el contenido recuperado. sino no hace falta.
		contenido->setContenido(valorRecuperado);
	}
	else
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta: '" + contenido->getPath() + "' no existe.", this->nombreClase() + ".sacarArchivoLogicoDeContenido()");
		return false;
	}

	if ( this->existeArchivoLogicoEnContenidoDeCarpeta( archivoLogico, contenido ) == false )
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta '"+ contenido->getPath() +"' no contiene al archivo logico '" + archivoLogico->getPath() + "'.", this->nombreClase() + ".sacarArchivoLogicoDeContenido()");
		return false;
	}

	std::vector<std::string> listaArchivos = contenido->getArchivos();

	contenido->eliminarArchivo( archivoLogico->getPath() );

	contenido->guardar();
	//contenido->modificar();

	return true;
}
bool Acciones::sacarCarpetaLogicaDeContenido(ConexionServidor::BaseDeDatos::CarpetaLogica* carpetaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido )
{
	std::string valorRecuperado = contenido->recuperar();

	if ( valorRecuperado.compare("vacio") != 0 )
	{// si recupero algo, entonces lo seteo el contenido recuperado. sino no hace falta.
		contenido->setContenido(valorRecuperado);
	}
	else
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta: '" + contenido->getPath() + "' no existe.", this->nombreClase() + ".sacarCarpetaLogicaDeContenido()");
		return false;
	}

	if ( this->existeCarpetaLogicaEnContenidoDeCarpeta( carpetaLogica, contenido ) == false )
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta '"+ contenido->getPath() +"' no contiene a la carpeta logica '" + carpetaLogica->getPath() + "'.", this->nombreClase() + ".sacarCarpetaLogicaDeContenido()");
		return false;
	}

	std::vector<std::string> listaArchivos = contenido->getArchivos();

	contenido->eliminarCarpeta( carpetaLogica->getPath() );

	contenido->modificar();
	//contenido->guardar();

	return true;
}
bool Acciones::modificarArchivoLogico(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogicoNuevo)
{
	ConexionServidor::BaseDeDatos::ArchivoLogico archivoActual;
	archivoActual.setPath( archivoLogicoNuevo->getPath() );
	std::string valorRecuperadoActual = archivoActual.recuperar();
	if ( valorRecuperadoActual.compare("vacio") == 0 )
	{
		Utiles::Log::instancia()->debug("Usuario '" + archivoActual.getPath() +"' no existe logicamente.", this->nombreClase() + ".modificarArchivoLogico()");
		return false;
	}
	archivoActual.setContenido(valorRecuperadoActual);

//	std::vector<std::string> etiquetas = archivoActual.getEtiquetas();
//	for ( unsigned int i = 0 ; i < etiquetas.size() ; i++ )
//	{
//		archivoLogicoNuevo->agregarEtiqueta( etiquetas[i] );
//	}

	std::vector<std::string> compartidoCon = archivoActual.getCompartidoCon();
	for ( unsigned int i = 0 ; i < compartidoCon.size() ; i++ )
	{
		archivoLogicoNuevo->agregarCompartidoCon( compartidoCon[i] );
	}

	int versionActual = Utiles::Metodos::toInt( archivoActual.getVersion() );
	int versionNueva = versionActual + 1;

	archivoLogicoNuevo->setVersion( Utiles::Metodos::toString(versionNueva) );
	archivoLogicoNuevo->modificar();

	Utiles::Log::instancia()->debug( "version Actual: " + archivoActual.getVersion() + " version Nueva: " + archivoLogicoNuevo->getVersion() + ".", this->nombreClase() + ".modificarArchivoLogico()");

	Utiles::Log::instancia()->debug("Nuevos datos de archivo: \n"+ archivoLogicoNuevo->getContenido(), this->nombreClase() + ".modificarArchivoLogico()");

	return true;
}
bool Acciones::modificarArchivoFisico(ConexionServidor::BaseDeDatos::Archivo* archivoFisicoNuevo)
{
	if ( archivoFisicoNuevo->existeFisicamente() == false )
	{
		Utiles::Log::instancia()->debug("No existe fisicamente el archivo '"+ archivoFisicoNuevo->getPath() +"' que se quiere modificar.", this->nombreClase() + ".modificarArchivoFisico()");
		return false;
	}

	archivoFisicoNuevo->eliminarFisicamente();
	archivoFisicoNuevo->guardarFisicamente();

	if ( archivoFisicoNuevo->existeFisicamente() )
	{
		Utiles::Log::instancia()->debug("Se modifico fisicamente el archivo '"+ archivoFisicoNuevo->getPath() +"'.", this->nombreClase() + ".modificarArchivoFisico()");
		return true;
	}
	else
	{
		Utiles::Log::instancia()->debug("No se guardo fisicamente el archivo '"+ archivoFisicoNuevo->getPath() +"' que se queria modificar.", this->nombreClase() + ".modificarArchivoFisico()");
		return false;
	}
}

// ---------- complejos ---------- //
bool Acciones::agregarArchivoLogicoASuCarpetaLogica(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;
	contenidoEnCarpeta.setPath( archivoLogico->getDireccion() );

	bool res = this->agregarArchivoLogicoAContenido( archivoLogico, &contenidoEnCarpeta );

	return res;
}
bool Acciones::sacarArchivoLogicoDeSuCarpetaLogica(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;
	contenidoEnCarpeta.setPath( archivoLogico->getDireccion() );

	std::string valorRecuperado = contenidoEnCarpeta.recuperar();
	if ( valorRecuperado.compare("vacio") != 0 )
	{
		contenidoEnCarpeta.setContenido( valorRecuperado );
	}

	if ( this->existeArchivoLogicoEnContenidoDeCarpeta( archivoLogico, &contenidoEnCarpeta ) == false )
	{
		Utiles::Log::instancia()->debug("ContenidoEnCarpeta '"+ contenidoEnCarpeta.getPath() +"' no contiene al archivo logico '" + archivoLogico->getPath() + "'.", this->nombreClase());
		return false;
	}

	std::vector<std::string> listaArchivos = contenidoEnCarpeta.getArchivos();

	contenidoEnCarpeta.eliminarArchivo( archivoLogico->getPath() );

	contenidoEnCarpeta.guardar();

	return true;
}

bool Acciones::agregarArchivoLogicoAPapelera(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta papelera;

	papelera.setPath( archivoLogico->getPropietario() + "/" + InfoOperaciones::papelera );

	bool res = this->agregarArchivoLogicoAContenido( archivoLogico, &papelera );

	return res;
}

bool Acciones::existeArchivoLogicoEnContenidoDeCarpeta(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido )
{
	std::vector<std::string> listaArchivos = contenido->getArchivos();

	if ( listaArchivos.size() == 0 )
	{
		return false;
	}

	for ( unsigned int i = 0 ; i < listaArchivos.size() ; i++ )
	{// chequeo si existe el archivo que voy a agregar.

		if ( listaArchivos[i].compare( archivoLogico->getPath() ) == 0 )
		{// si existe, salgo del for.
			break;
		}
		// si no existe, entonces devuelvo FALSE.
		return false;
	}
	return true;
}
bool Acciones::existeCarpetaLogicaEnContenidoDeCarpeta(ConexionServidor::BaseDeDatos::CarpetaLogica* carpetaLogica, ConexionServidor::BaseDeDatos::ContenidoPorCarpeta* contenido )
{
	std::vector<std::string> listaCarpetas = contenido->getCarpetas();

	if ( listaCarpetas.size() == 0 )
	{
		return false;
	}

	for ( unsigned int i = 0 ; i < listaCarpetas.size() ; i++ )
	{// chequeo si existe el archivo que voy a agregar.

		if ( listaCarpetas[i].compare( carpetaLogica->getPath() ) == 0 )
		{// si existe, salgo del for.
			break;
		}
		// si no existe, entonces devuelvo FALSE.
		return false;
	}
	return true;
}

bool Acciones::crearVersionInicialDeArchivo(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	ConexionServidor::BaseDeDatos::VersionDeArchivoPorUsuario version;

	version.setPathArchivo( archivoLogico->getPath() );
	version.setUsuario( archivoLogico->getPropietario() );
	version.setVersion( "1" );

	version.guardar();

	Utiles::Log::instancia()->debug( "Creada version: '" + archivoLogico->getPath() + "' , '" + archivoLogico->getPropietario() + "' ", this->nombreClase() );

	return true;
}

bool Acciones::agregarArchivoALaListaDeArchivosDeUsuario(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	ConexionServidor::BaseDeDatos::ContenidoPorCarpeta contenidoEnCarpeta;
	contenidoEnCarpeta.setPath( archivoLogico->getPropietario() + "/" + InfoOperaciones::carpetaArchivosPorUsuario );

	bool res = this->agregarArchivoLogicoAContenido( archivoLogico, &contenidoEnCarpeta );

	return res;
}
bool Acciones::versionDeUltimoModificadorEstaActualizada(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico)
{
	ConexionServidor::BaseDeDatos::VersionDeArchivoPorUsuario versionModificador;
	versionModificador.setUsuario( archivoLogico->getUltimoUsuarioModif() );
	versionModificador.setPathArchivo( archivoLogico->getPath() );

	std::string valorRecuperado = versionModificador.recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		Utiles::Log::instancia()->warn( "No existe version del archivo '" + archivoLogico->getPath() + " para el usuario: '" + archivoLogico->getUltimoUsuarioModif() + "'.", this->nombreClase() );
		return false;
	}
	versionModificador.setContenido( valorRecuperado );

	valorRecuperado = archivoLogico->recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		Utiles::Log::instancia()->warn( "No existe logicamente el archivo '" + archivoLogico->getPath() + "'.", this->nombreClase() );
		return false;
	}
	ConexionServidor::BaseDeDatos::ArchivoLogico archivoAuxversion( valorRecuperado );

	int vsModif = Utiles::Metodos::toInt( versionModificador.getVersion() );
	int vsActual = Utiles::Metodos::toInt( archivoAuxversion.getVersion() );
	Utiles::Log::instancia()->debug( "version Modif: " + versionModificador.getVersion() + " version Actual: " + archivoAuxversion.getVersion() + ".", this->nombreClase() );
	if ( vsModif < vsActual )
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Acciones::actualizarVersionDeUltimoModificador(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogicoNuevo)
{
	ConexionServidor::BaseDeDatos::VersionDeArchivoPorUsuario versionModificador;
	versionModificador.setUsuario( archivoLogicoNuevo->getUltimoUsuarioModif() );
	versionModificador.setPathArchivo( archivoLogicoNuevo->getPath() );

	std::string valorRecuperado = versionModificador.recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		Utiles::Log::instancia()->debug( "valorRecuperado versionModificador: " + valorRecuperado, this->nombreClase() );
		return false;
	}
	versionModificador.setContenido( valorRecuperado );

	int versionActual = Utiles::Metodos::toInt( versionModificador.getVersion() );
	int versionNueva = versionActual + 1;

	versionModificador.setVersion( Utiles::Metodos::toString( versionNueva ) );

	versionModificador.modificar();

	Utiles::Log::instancia()->debug( "Version: '" + versionModificador.getPathArchivo() + "-" + versionModificador.getUsuario() + "' actualizado de " + Utiles::Metodos::toString(versionActual) + " a " + versionModificador.getVersion() + ".", this->nombreClase() );

	return false;
}
bool Acciones::actualizarVersionDelQueDescarga(ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico, ConexionServidor::BaseDeDatos::User* usuario)
{
	ConexionServidor::BaseDeDatos::VersionDeArchivoPorUsuario versionDescargador;
	versionDescargador.setUsuario( usuario->getEmail() );
	versionDescargador.setPathArchivo( archivoLogico->getPath() );

	std::string valorRecuperado = versionDescargador.recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		Utiles::Log::instancia()->warn( "No existe el usuario '" + usuario->getEmail() + "' que quiere realizar la descargar.", this->nombreClase() );
		return false;
	}
	versionDescargador.setContenido( valorRecuperado );

	valorRecuperado = archivoLogico->recuperar();
	if ( valorRecuperado.compare("vacio") == 0 )
	{
		Utiles::Log::instancia()->warn( "No existe logicamente el archivo '" + archivoLogico->getPath() + "'.", this->nombreClase() );
		return false;
	}
	archivoLogico->setContenido( valorRecuperado );

	std::string versionActual = versionDescargador.getVersion();

	versionDescargador.setVersion( archivoLogico->getVersion() );

	versionDescargador.modificar();

	Utiles::Log::instancia()->debug( "Version: '" + versionDescargador.getPathArchivo() + "-" + versionDescargador.getUsuario() + "' actualizado de " + versionActual + " a " + versionDescargador.getVersion() + ".", this->nombreClase() );
	return true;
}

ConexionServidor::BaseDeDatos::ArchivoLogico* Acciones::parsearArchivoDeQuery( std::string query )
{
	std::vector<std::string> parametros = Utiles::Metodos::split( query, '&' );
	ConexionServidor::BaseDeDatos::ArchivoLogico* archivoLogico = new ConexionServidor::BaseDeDatos::ArchivoLogico();

	for ( unsigned int i = 0 ; i < parametros.size() ; i++ )
	{
		std::vector<std::string> valores = Utiles::Metodos::split( parametros[i], '=' );
		std::string parametro = valores[0];
		std::string valor = valores[1];

		//replace( valor.begin(), valor.end(), '+', ' ' );

		if ( parametro.compare("nombre") == 0 )
		{
			archivoLogico->setNombre( valor );
		}else if ( parametro.compare("extension") == 0 )
		{
			archivoLogico->setExtension( valor );
		}else if ( parametro.compare("etiqueta") == 0 )
		{

			std::vector<std::string> etiquetas = Utiles::Metodos::split( valor, ' ' );
			for ( unsigned int j = 0 ; j < etiquetas.size() ; j++ )
			{
				//std::string desencodeado = base64_decode( etiquetas[j] );
				//archivoLogico->agregarEtiqueta( desencodeado );
				archivoLogico->agregarEtiqueta( etiquetas[j]);
			}
		}else if ( parametro.compare("fecha_ulti_modi") == 0 )
		{
			std::string desencodeado = base64_decode( valor );
			archivoLogico->setUltimaFechaModif( desencodeado );
		}else if ( parametro.compare("usuario_ulti_modi") == 0 )
		{
			archivoLogico->setUltimoUsuarioModif( valor );
		}else if ( parametro.compare("usuario_ulti_modi") == 0 )
		{
			archivoLogico->setUltimoUsuarioModif( valor );
		}else if ( parametro.compare("propietario") == 0 )
		{
			archivoLogico->setPropietario( valor );
		}else if ( parametro.compare("usuario_ulti_modi") == 0 )
		{
			archivoLogico->setUltimoUsuarioModif( valor );
		}else if ( parametro.compare("baja_logica") == 0 )
		{
			archivoLogico->setBajaLogica( valor );
		}else if ( parametro.compare("direccion") == 0 )
		{
			archivoLogico->setDireccion( valor );
		}
	}

	return archivoLogico;
}
//std::vector<std::string> Acciones::obtenerEtiquetas(std::string etiquetasEncodeadas)
//{
//	std::string etiquetas = base64_decode( etiquetasEncodeadas );
//
//	etiquetas.replace( etiquetas.begin(), etiquetas.end(), '[','' );
//}
std::string Acciones::nombreClase()
{
	return "Acciones";
}

