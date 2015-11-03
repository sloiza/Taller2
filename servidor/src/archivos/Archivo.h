/*
 * Archivo.h
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#ifndef ARCHIVO_H_
#define ARCHIVO_H_

// utiles
#include "../utiles/utiles.h"
#include "../utiles/Bytes.h"

// entidades
#include "../bd/entidades/EntidadBD.h"
#include "../bd/entidades/ArchivoLogico.h"

// manager archivos
#include "../archivos/ManagerArchivos.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class Archivo: public EntidadDB {
public:
	Archivo();
	Archivo(std::string datosLogicos);
	virtual ~Archivo();

	void setBytes(Utiles::Bytes* bytes);
	void setDireccion(std::string);

	Utiles::Bytes* getBytes();
	const char* getTiraDeBytes();
	std::string getDireccion();
	std::string getPath();

	// Metodos de EntidadDB
	virtual std::string getValor();

	virtual void guardar(); 		// PUT
	virtual void modificar(); 	// POST
	virtual void eliminar(); 	// DELETE
	virtual std::string recuperar(); 	// GET

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();

	ArchivoLogico* archivoLogico;
	std::string direccion;
	Utiles::Bytes* bytes;
};
};
};


#endif /* ARCHIVO_H_ */
