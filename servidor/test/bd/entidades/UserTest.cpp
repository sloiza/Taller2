/*
 * UserTest.cpp
 *
 *  Created on: 25/10/2015
 *      Author: manuel
 */

#include "UserTest.h"

using namespace Test;

const std::string UserTest::usuarioEjemplo =
"{\"nombre\":\"Arturo\",\"apellido\":\"Perez\",\"mail\":\"arthur@gmail.com\", \"foto\":\"pathAFoto\", \"lugar\":\"Buenos Aires\", \"id\":1234}";

UserTest::UserTest() : user(NULL)
{
	this->setUp();
}

UserTest::~UserTest()
{
	this->terminando();
}

void UserTest::testCrearYRecuperarEnBDCorrectamente()
{
	this->user->guardar();

	std::string contenidoRecuperado = this->user->recuperar();

	ConexionServidor::BaseDeDatos::User usuarioRecuperado;
	usuarioRecuperado.setContenido(contenidoRecuperado);

	//std::cout << contenidoRecuperado << "\n";

	EXPECT_STREQ(this->user->getContenido().c_str(), usuarioRecuperado.getContenido().c_str());
}

void UserTest::testModificarEnBDCorrectamente()
{
	this->user->guardar();

	EXPECT_STREQ("Arturo", this->user->getName().c_str());
	EXPECT_STREQ("Perez", this->user->getLastName().c_str());

	this->user->setName("Pedro");
	this->user->setLastName("Sanchez");
	this->user->setEmail( "hola@gmail.com" );
	this->user->setProfilePhoto( "fotitoturra" );
	this->user->setLocation( "location" );
	this->user->setPassword( "newpass" );
	this->user->setID( "newID" );

	this->user->modificar();

	std::string contenidoNuevo = this->user->recuperar();

	ConexionServidor::BaseDeDatos::User usuarioNuevo;
	usuarioNuevo.setContenido(contenidoNuevo);

	EXPECT_STREQ("Pedro", usuarioNuevo.getName().c_str());
	EXPECT_STREQ("Sanchez", usuarioNuevo.getLastName().c_str());
	EXPECT_STREQ("hola@gmail.com", usuarioNuevo.getEmail().c_str());
	EXPECT_STREQ("fotitoturra", usuarioNuevo.getProfilePhoto().c_str());
	EXPECT_STREQ("location", usuarioNuevo.getLocation().c_str());
	EXPECT_STREQ("newpass", usuarioNuevo.getPassword().c_str());
	EXPECT_STREQ("newID", usuarioNuevo.getID().c_str());
}

void UserTest::testEliminarEnBDCorrectamente()
{

}

void UserTest::testModificarAtributoCorrectamente()
{
	std::string nombre = this->user->getName();

	EXPECT_STREQ("Arturo", nombre.c_str());

	this->user->setName("Pedro");

	std::string nombreNuevo = this->user->getName();

	EXPECT_STREQ("Pedro", nombreNuevo.c_str());
}

void UserTest::setUp()
{
	this->user = new ConexionServidor::BaseDeDatos::User(usuarioEjemplo);
}

void UserTest::terminando()
{
	if ( this->user != NULL )
	{
		delete this->user;
		this->user = NULL;
	}
}

