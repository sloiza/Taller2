

#include "CreadorDeOperaciones.h"

using namespace ConexionServidor::Operaciones;

std::vector<std::string> CreadorDeOperaciones::campos(0);
CreadorDeOperaciones::Recurso* CreadorDeOperaciones::raiz = NULL;

CreadorDeOperaciones::CreadorDeOperaciones()
{
	crearArbolDeRecursos();
}

CreadorDeOperaciones::~CreadorDeOperaciones()
{
	liberarArbolDeRecursos();
}

void CreadorDeOperaciones::crearArbolDeRecursos()
{
	Recurso* principal = new Recurso();
	principal->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::PRINCIPAL];
	principal->tipo = InfoOperaciones::PRINCIPAL;

	Recurso* usuarios = new Recurso();
	usuarios->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::USUARIOS];
	usuarios->tipo = InfoOperaciones::USUARIOS;

//	Recurso* perfil = new Recurso();
//	perfil->nombre = "miPerfil";
//	perifl->operacion = new OperacionPerfil();

	Recurso* baul = new Recurso();
	baul->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::ARCHIVOS];
	baul->tipo = InfoOperaciones::ARCHIVOS;

	Recurso* carpetas = new Recurso();
	carpetas->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::CARPETAS];
	carpetas->tipo = InfoOperaciones::CARPETAS;

	Recurso* compartirArchivo = new Recurso();
	compartirArchivo->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::COMPARTIR_ARCHIVO];
	compartirArchivo->tipo = InfoOperaciones::COMPARTIR_ARCHIVO;

	Recurso* compartirCarpeta = new Recurso();
	compartirCarpeta->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::COMPARTIR_CARPETA];
	compartirCarpeta->tipo = InfoOperaciones::COMPARTIR_CARPETA;

	Recurso* descargarArchivo = new Recurso();
	descargarArchivo->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::DESCARGAR];
	descargarArchivo->tipo = InfoOperaciones::DESCARGAR;

	Recurso* papelera = new Recurso();
	papelera->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::PAPELERA];
	papelera->tipo = InfoOperaciones::PAPELERA;

	Recurso* busqueda = new Recurso();
	busqueda->nombre = InfoOperaciones::nombresRecursos[InfoOperaciones::BUSCAR];
	busqueda->tipo = InfoOperaciones::BUSCAR;

	principal->hijos.push_back(usuarios);
	principal->hijos.push_back(baul);
	//usuarios->hijos.push_back(perfil);
	principal->hijos.push_back(carpetas);
	principal->hijos.push_back(compartirArchivo);
	principal->hijos.push_back(compartirCarpeta);
	principal->hijos.push_back(descargarArchivo);
	principal->hijos.push_back(papelera);
	principal->hijos.push_back(busqueda);

	raiz = principal;
}

void CreadorDeOperaciones::liberarArbolDeRecursos()
{
	liberarRecusivamente(raiz);
}

std::vector<std::string> CreadorDeOperaciones::getCampos()
{
	return campos;
}

IOperable* CreadorDeOperaciones::getOperacion(ConexionServidor::Request::URI* uri)
{
    campos = uri->getRecursosDividos();

    std::cout << "uri: " << uri->getURI() << "\n";

    return reconocerUriRecursivamente(raiz, 1);
}

IOperable* CreadorDeOperaciones::reconocerUriRecursivamente(Recurso* recurso, int nivel)
{
    if ( campos.size() == (unsigned int) nivel )
    {
    	return crearOperacion( recurso->tipo );
    }


	for ( std::vector<Recurso*>::iterator hijo = recurso->hijos.begin(); hijo != recurso->hijos.end(); hijo++)
	{
		if ( (*hijo)->nombre == campos[nivel] )
		{
			nivel++;
			return reconocerUriRecursivamente(*hijo, nivel);
		}
	}

	return new OperacionErrorURL();
}

IOperable* CreadorDeOperaciones::crearOperacion(InfoOperaciones::OPERACIONES tipo)
{
	switch (tipo)
	{
		case InfoOperaciones::PRINCIPAL: return new OperacionPrincipal();
		case InfoOperaciones::USUARIOS: return new OperacionesUsuario();
		case InfoOperaciones::ARCHIVOS: return new OperacionesArchivos();
		case InfoOperaciones::CARPETAS: return new OperacionesCarpetas();
		case InfoOperaciones::COMPARTIR_ARCHIVO: return new OperacionCompartirArchivo();
		case InfoOperaciones::COMPARTIR_CARPETA: return new OperacionCompartirCarpeta();
		case InfoOperaciones::DESCARGAR: return new OperacionDescargarArchivo();
		case InfoOperaciones::PAPELERA: return new OperacionesPapelera();
		case InfoOperaciones::BUSCAR: return new OperacionBusqueda();
		default:
			{
				Utiles::Log::instancia()->warn("URL no mapeada.", nombreClase() );
				return new OperacionErrorURL();
			}
	}
}

void CreadorDeOperaciones::liberarRecusivamente(Recurso* recurso)
{
	if ( recurso == NULL )
	{
		return;
	}

	for ( std::vector<Recurso*>::iterator hijo = recurso->hijos.begin(); hijo != recurso->hijos.end(); hijo++)
	{
		liberarRecusivamente(*hijo);
		if ( *hijo != NULL )
		{
			delete (*hijo)->operacion;
			(*hijo)->operacion = NULL;
			delete *hijo;
			(*hijo) = NULL;
		}
	}
}

std::string CreadorDeOperaciones::nombreClase()
{
	return "CreadorDeOperaciones";
}
