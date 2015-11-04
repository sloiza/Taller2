/*
 * Carpeta.h
 *
 *  Created on: 3/11/2015
 *      Author: manuel
 */

#ifndef CARPETA_H_
#define CARPETA_H_

// entidades
#include "../bd/entidades/EntidadBD.h"
#include "../bd/entidades/CarpetaLogica.h"

// manager archivos
#include "../archivos/ManagerArchivos.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class Carpeta : public EntidadDB
{
public:
	Carpeta();
	Carpeta(std::string datosLogicos);
	virtual ~Carpeta();

	virtual void guardar(); 		// PUT
	virtual void modificar(); 	// POST
	virtual void eliminar(); 	// DELETE
	virtual std::string recuperar(); 	// GET

	std::string getPath();

	// Metodos de EntidadDB
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();

private:

	CarpetaLogica* carpetaLogica;
	//ContenidoPorCarpeta* contenido;

};
};
};

#endif /* CARPETA_H_ */
