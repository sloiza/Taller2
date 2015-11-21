/*
 * ServidorMultihilo.cpp
 *
 *  Created on: 19/11/2015
 *      Author: manuel
 */

#include "ServidorMultihilo.h"

using namespace ConexionServidor;

bool ServidorMultihilo::corriendo = false;

ServidorMultihilo::ServidorMultihilo() : servidores(0), puerto(0) {}

ServidorMultihilo::~ServidorMultihilo()
{
	this->destruir();
}

void ServidorMultihilo::crear()
{
	for ( unsigned int i = 0 ; i < servidores.size() ; i++ )
	{
		std::string indice = Utiles::Metodos::toString( i );
		this->servidores[i] = mg_create_server( (void*) indice.c_str() , HandlerEventos::handler);
	}

	//mg_set_option(this->servidores[0], "document_root", ".");
	mg_set_option(this->servidores[0], "listening_port", Utiles::Metodos::toString(this->puerto).c_str());

	for ( unsigned int i = 1 ; i < servidores.size() ; i++ )
	{
		  mg_copy_listeners(this->servidores[0], this->servidores[i]);
	}

	signal(SIGINT, ServidorMultihilo::handlerSenial);
	corriendo = true;
	Operaciones::CreadorDeOperaciones::crearArbolDeRecursos();

	Utiles::Log::instancia()->debug("Servidor creado en puerto " + Utiles::Metodos::toString(this->puerto) + " con " + Utiles::Metodos::toString(servidores.size()) + " hilos.", this->nombreClase() );
}

void ServidorMultihilo::setNumeroDeHilos(int numeroDeHilos)
{
	this->servidores.resize(numeroDeHilos);
}
void ServidorMultihilo::setPuerto(int puerto)
{
	this->puerto = puerto;
}
void ServidorMultihilo::setOpcion(std::string nombre, std::string valor)
{

}

void* ServidorMultihilo::servir(void *server)
{
  while ( corriendo )
  {
	  mg_poll_server((struct mg_server *) server, 40000);
  }

  return NULL;
}

void ServidorMultihilo::comenzarAEscuchar()
{
	Utiles::Log::instancia()->debug("Servidor comienza a escuchar.", this->nombreClase() );

	for ( unsigned int i = 0 ; i < servidores.size() ; i++ )
	{
	  mg_start_thread(servir, servidores[i]);
	}
}
bool ServidorMultihilo::estaCorriendo()
{
	return corriendo;
}

void ServidorMultihilo::handlerSenial(int sig)
{
	corriendo = false;
}

void ServidorMultihilo::destruir()
{
	for ( unsigned int i = 0 ; i < servidores.size() ; i++ )
	{
		if ( this->servidores[i] != NULL)
		{
			mg_destroy_server(&this->servidores[i]);
		}
	}
	Operaciones::CreadorDeOperaciones::liberarArbolDeRecursos();
}

std::string ServidorMultihilo::nombreClase()
{
	return "ServidorMultihilo";
}
