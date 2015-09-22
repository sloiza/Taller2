/*
 * Servidor.cpp
 *
 *  Created on: 16/9/2015
 *      Author: manuel
 */

#include "Servidor.h"

using namespace ConexionServidor;

bool Servidor::corriendo = true;

Servidor::Servidor() : servidorMG(NULL), puerto(0) {}

Servidor::~Servidor()
{
	this->destruir();
}

void Servidor::crear()
{
	this->servidorMG = mg_create_server(NULL, HandlerEventos::handler );
	this->setPuerto(8080);
	this->setOpcion("document_root", ".");
	signal(SIGINT, Servidor::handlerSenial);
}

void Servidor::crear(int puerto)
{
	this->crear();
	this->setPuerto(puerto);
}

void Servidor::setPuerto(int numero)
{
	mg_set_option(this->servidorMG, "listening_port", Utiles::toString(numero).c_str());
	this->puerto = numero;
}

void Servidor::setOpcion(std::string nombre, std::string valor)
{
	mg_set_option(this->servidorMG, nombre.c_str(), valor.c_str());
}

bool Servidor::estaCorriendo()
{
	return corriendo;
}

void Servidor::correr(int milisegs)
{
	mg_poll_server(this->servidorMG, milisegs);
}

void Servidor::destruir()
{
	if ( this->servidorMG != NULL)
	{
		mg_destroy_server(&this->servidorMG);
	}
}

void Servidor::handlerSenial(int sig)
{
	corriendo = false;
}
