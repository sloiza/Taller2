#include "User.h"

using namespace ConexionServidor::BaseDeDatos;

const std::string User::etiquetas[] = {"nombre", "apellido", "password","mail", "foto", "lugar", "nick", "id" };

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
	return this->info->getAtributo(etiquetas[NOMBRE], "nombreDefault");
}
void User::setName(string nombre){
	this->info->setAtributo(etiquetas[NOMBRE], nombre);
}
string User::getLastName(){
	return this->info->getAtributo(etiquetas[APELLIDO], "apellidoDefault");
}
void User::setLastName(string lastName){
	this->info->setAtributo(etiquetas[APELLIDO], lastName);
}

string User::getNickName(){
	return this->info->getAtributo(etiquetas[NICK], "nickDefault");
}

void User::setNickName(string nickName){
	this->info->setAtributo(etiquetas[NICK], nickName);
}

string User::getEmail(){
	return this->info->getAtributo(etiquetas[MAIL], "mailDefault");
}
void User::setEmail(string email){
	this->info->setAtributo(etiquetas[MAIL], email);
}
string User::getProfilePhoto(){
	return this->info->getAtributo(etiquetas[FOTO], "fotoDefault");
}
void User::setProfilePhoto(string pathProf){
	this->info->setAtributo(etiquetas[FOTO], pathProf);
}
string User::getLocation(){
	return this->info->getAtributo(etiquetas[LUGAR], "lugarDefault");
}
void User::setLocation(string location){
	this->info->setAtributo(etiquetas[LUGAR], location);
}

std::string User::getPassword()
{
	return this->info->getAtributo(etiquetas[PASSWORD], "passwordDefault");
}
void User::setPassword(std::string password)
{
	this->info->setAtributo(etiquetas[PASSWORD], password);
}

std::string User::getID()
{
	return this->info->getAtributo(etiquetas[ID], "SIN-ID");
}

void User::setID(std::string id)
{
	this->info->setAtributo(etiquetas[ID], id);
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
	return this->getEmail();
}
	
