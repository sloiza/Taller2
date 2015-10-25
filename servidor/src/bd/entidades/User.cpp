#include "User.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string User::etiquetas[] = {"nombre", "apellido", "mail", "foto", "lugar", "nick", "id" };

User::User(std::string contenido)
{
	this->info->setContenido(contenido);
}

User::User() {}

User::User(string firstName, string lastName, string nickName, string email, string pathProf,string location) {
	this->setName(firstName);
	this->setLastName(lastName);
	this->setNickName(nickName);
	this->setEmail(email);
	this->setProfilePhoto(pathProf);
	this->setLocation(location);
}

User::~User()
{

}

string User::getName(){
	//return this->firstName;
	return this->info->getAtributo(etiquetas[NOMBRE], "nombreDefault");
}
void User::setName(string nombre){
	//this->firstName = firstName;
	this->info->setAtributo(etiquetas[NOMBRE], nombre);
}
string User::getLastName(){
	//return this->lastName;
	return this->info->getAtributo(etiquetas[APELLIDO], "apellidoDefault");
}
void User::setLastName(string lastName){
	//this->lastName = lastName;
	this->info->setAtributo(etiquetas[APELLIDO], lastName);
}

string User::getNickName(){
	//return this->nickName;
	return this->info->getAtributo(etiquetas[NICK], "nickDefault");
}

void User::setNickName(string nickName){
	//this->nickName = nickName;
	this->info->setAtributo(etiquetas[NICK], nickName);
}

string User::getEmail(){
	//return this->email;
	return this->info->getAtributo(etiquetas[MAIL], "mailDefault");
}
void User::setEmail(string email){
	//this->email = email;
	this->info->setAtributo(etiquetas[MAIL], email);
}
string User::getProfilePhoto(){
	//return this->pathProf;
	return this->info->getAtributo(etiquetas[FOTO], "fotoDefault");
}
void User::setProfilePhoto(string pathProf){
	//this->pathProf = pathProf;
	this->info->setAtributo(etiquetas[FOTO], pathProf);
}
string User::getLocation(){
	//return this->location;
	return this->info->getAtributo(etiquetas[LUGAR], "lugarDefault");
}
void User::setLocation(string location){
	//this->location = location;
	this->info->setAtributo(etiquetas[LUGAR], location);
}

//void User::setStatus(bool st){
//	this->status = st;
//}
//bool User::getStatus(){
//	return this->status;
//}

// Metodos de EntidadDB
std::string User::getValor()
{
	return this->info->getContenido();
}

std::string User::getColumnaDeFamilia()
{
	return "user";
}

std::string User::getClave()
{
	return this->getName();
}
	
