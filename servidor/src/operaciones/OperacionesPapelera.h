

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

class OperacionesPapelera : public IOperable
{
public:
	OperacionesPapelera();
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
	ConexionServidor::Respuesta put(Utiles::Bytes* contenido, std::string query);

	void imprimir();

	bool restaurarCarpeta(Utiles::Bytes* contenido, std::string mailDeUsuario);

};
};
};

#endif /* OPERACIONESPAPELERA_H_ */
