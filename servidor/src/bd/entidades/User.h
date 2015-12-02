/// \file User.h
/// \date 2015-11-26
/// \brief Clase que representa a un usuario logico.
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

namespace ConexionServidor
{
namespace BaseDeDatos
{
/// \brief Clase que representa a un usuario logico.
class User : public EntidadDB
{

public:

	enum enumEtiquetas
	{
		NOMBRE,
		APELLIDO,
		PASSWORD,
		MAIL,
		FOTO,
		LUGAR,
		NICK,
		ID
	};

	static const std::string etiquetas[];
	/// \brief Constructor.
	User();
	/**
	 * @brief Constructor: Crea una instancia de User  dado un json
	 */
	User(std::string contenido);

	/// \brief Destructor.
	virtual ~User();
	/**
	 * @brief Devuelve un string con el nombre del usuario
	 */
	string getName();
	/**
	 * @brief Setea el nombre del usuario
	 */
	void setName(string name);
	/**
	 * @brief Devuelve un string con el apellido del usuario
	 */
	string getLastName();
	/**
	 * @brief Setea el apellido del usuario
	 */
	void setLastName(string lastName);
	/**
	 * @brief Devuelve un string con el mail del usuario
	 */
	string getEmail();
	/**
	 * @brief Setea el mail del usuario
	 */
	void setEmail(string email);
	/**
	 * @brief Devuelve un string con el path de la foto del usuario
	 */
	string getProfilePhoto();
	/**
	 * @brief Setea el path de la foto del usuario
	 */
	void setProfilePhoto(string pathProf);
	/**
	 * @brief Devuelve un string con la localización del usuario
	 */
	string getLocation();
	/**
	 * @brief Setea la localización del usuario
	 */
	void setLocation(string location);
	/**
	 * @brief Setea el status del usuario
	 */
	void setStatus(bool st);
	/**
	 * @brief Devuelve un bool con el status del usuario
	 */
	bool getStatus();
	/**
	 * @brief Devuelve un string con el password del usuario
	 */
	std::string getPassword();
	/**
	 * @brief Setea el password del usuario
	 */
	void setPassword(std::string password);
	/**
	 * @brief Devuelve un string con el id del usuario
	 */
	std::string getID();
	/**
	 * @brief Setea el id del usuario
	 */
	void setID(std::string id);

	/**
	 * @brief Devuelve un string con el json asociado al usuario
	 */
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();
};
};
};

#endif /* USER_H_ */
