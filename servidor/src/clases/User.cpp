
#include "User.h"

User::User(){
	this->firstName = "";
	this->lastName = "";
	this->email = "";
	this->pathProf = "";
	this->location = "";
		
}
User::User(string firstName, string lastName, string nickName, string email, string pathProf,string location) : status(true) {
	this->firstName = firstName;
	this->lastName = lastName;
	this->nickName = nickName;
	this->email = email;
	this->pathProf = pathProf;
	this->location = location;
}
User::~User(){

}
string User::getName(){
	return this->firstName;

}
void User::setName(string name){
	this->firstName = firstName;

}
string User::getLastName(){
	return this->lastName;
}
void User::setLastName(string lastName){
	this->lastName = lastName;
}

string User::getNickName(){
	return this->nickName;
}

void User::setNickName(string nickName){
	this->nickName = nickName;
}

string User::getEmail(){
	return this->email;
}
void User::setEmail(string email){
	this->email = email;
}
string User::getProfilePhoto(){
	return this->pathProf;
}
void User::setProfilePhoto(string pathProf){
	this->pathProf = pathProf;
}
string User::getLocation(){
	return this->location;
}
void User::setLocation(string location){
	this->location = location;
}

void User::setStatus(bool st){
	this->status = st;
}
bool User::getStatus(){
	return this->status;
}

string User::toJson(){

	//VER SI ES VACIO 
	stringstream out;

	out << "{\"firstName\":\"" << this->firstName << "\",\"lastName\":\"" << this->lastName << "\",\"nickName\":\"" << this->nickName
		<< "\",\"email\":\"" << this->email << "\",\"location\":\"" << this->location << "\",\"id\":\"" << this->id << "\",\"status\":\""<< this->status << "\"}";
	return out.str();
}
void User::fromJson(string json){
	json = "{\"firstName\":\"Samanta\",\"lastName\":\"Loiza\",\"nickName\":\"\",\"email\":\"samiloiza@gmail.com\",\"location\":\"Argentina\",\"id\":\"0\"}}";
	vector<string> vec = split(json.c_str(), ',');	
	 for (size_t i = 0; i< vec.size(); i++){
        cout << vec[i] << endl;
    }


}

Status User::get(Slice key, string* value){
	//key alguna unique key generada con los datos del user
	//Clase amiga? o ver como tener instancia de la db
	//return rocks_db::get(this->colName, key, value);

}

	