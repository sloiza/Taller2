#ifndef USER_H_
#define USER_H_
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>


// utiles
#include "../../utiles/utiles.h"

// Base de datos
#include "EntidadBD.h"
#include "../JsonInfo.h"
#include "../rocks_db.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
	
class User : public EntidadDB
{

public:

	enum enumEtiquetas
	{
		NOMBRE,
		APELLIDO,
		MAIL,
		FOTO,
		LUGAR,
		NICK,
		ID
	};

	static const std::string etiquetas[];

	User();
	User(std::string contenido);
	User(string firstName, string lastName, string nickName, string email, string pathProf,string location);
	virtual ~User();
	string getName();
	void setName(string name);
	string getLastName();
	void setLastName(string lastName);
	string getEmail();
	void setEmail(string email);
	string getProfilePhoto();
	void setProfilePhoto(string pathProf);
	string getLocation();
	void setLocation(string location);
	string getNickName();
	void setNickName(string nickName);
	double getID();
	void setStatus(bool st);
	bool getStatus();

	// Metodos de EntidadDB
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();
};
};
};

#endif /* USER_H_ */
