/// \file OperacionesPapelera.h
/// \date 2015-11-26
/// \brief Clase que realiza las operaciones de la papelera.
#ifndef OPERACIONESPAPELERA_H_
#define OPERACIONESPAPELERA_H_

// Operaciones
#include "IOperable.h"
#include "InfoOperaciones.h"
// entidadaes
#include "../bd/entidades/ContenidoPorCarpeta.h"
#include "../bd/entidades/User.h"
#include "../bd/entidades/ArchivoLogico.h"
#include "../bd/entidades/CarpetaLogica.h"
// STL
#include <iostream>
#include <string>

namespace ConexionServidor
{

namespace Operaciones
{
/// \brief Clase que realiza las operaciones de la papelera.
class OperacionesPapelera : public IOperable
{
public:
	/// \brief Constructor.
	OperacionesPapelera();
	/// \brief Destructor.
	virtual ~OperacionesPapelera();
	/**
	 * @brief Elimina la papelera
	 */
	ConexionServidor::Respuesta delet(Utiles::Bytes* contenido, std::string query);
	/**
	 * @brief Obtiene archivos de la papelera
	 */
	ConexionServidor::Respuesta get(Utiles::Bytes* contenido, std::string query);
	/**
	 * @brief Agrega archivos a la papelera
	 */
	ConexionServidor::Respuesta post(Utiles::Bytes* contenido, std::string query);
	/// \brief Ejecuta el metodo PUT.
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	/// \brief Imprime la operacion.
	void imprimir();

	/// \brief Restaura la carpeta de la papelera.
	bool restaurarCarpeta(Utiles::Bytes* contenido, std::string mailDeUsuario);

};
};
};

#endif /* OPERACIONESPAPELERA_H_ */
