/// \file OperacionesUsuario.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de usuario.
#ifndef OPERACIONESUSUARIO_H_
#define OPERACIONESUSUARIO_H_

// conexion
#include "../conexion/Respuesta.h"
// entidades
#include "../bd/entidades/User.h"
// carpetas
#include "../archivos/Carpeta.h"
// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"

// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Clase que realiza las operaciones de usuario.
class OperacionesUsuario : public IOperable {

public:
	/**
	 * @brief Clase que se encarga de ejecutar los métodos de Usuario.
	 */
	OperacionesUsuario();
	virtual ~OperacionesUsuario();
	/**
	 * @brief Se encarga de eliminar un Usuario.
	 *
	 * @param contenido 	
	 * @param query
	 *
	 * @retval Respuesta
	 */
	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	/**
	 * @brief Se encarga de obtener los datos de un Usuario.
	 *
	 * @param contenido 	
	 * @param query
	 *
	 * @retval Respuesta
	 */
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	/**
	 * @brief Se encarga de crear un Usuario.
	 *
	 * @param contenido 	
	 * @param query
	 *
	 * @retval Respuesta
	 */
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	/**
	 * @brief Se encarga de modificar un Usuario.
	 *
	 * @param contenido 	
	 * @param query
	 *
	 * @retval Respuesta
	 */
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	/// \brief Imprime la operacion.
	void imprimir();

private:
	/// \brief Chequea si existe el usuario.
	bool existeUsuarioConLosMismosDatos(std::string);
	/// \brief Chequea si el password es valido.
	bool passwordValido(std::string);
};
};
};

#endif /* OPERACIONESUSUARIO_H_ */
