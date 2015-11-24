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
#include "../bd/entidades/ContenidoPorCarpeta.h"

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

	void setNombre(std::string), setEtiqueta(std::string), setUltimaFechaModif(std::string),
			setUltimoUsuarioModif(std::string), setPropietario(std::string), setBajaLogica(std::string), setDireccion(std::string);

	std::string getNombre(), getEtiqueta(), getUltimaFechaModif(),
			getUltimoUsuarioModif(), getPropietario(), getBajaLogica(), getDireccion();

	std::string getPath();

	bool existeFisicamente();
	bool estaVacia();

	// Metodos de EntidadDB
	virtual std::string getValor();

	std::vector<std::string> getEtiquetas();
	void agregarEtiqueta(std::string);

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();

private:

	CarpetaLogica* carpetaLogica;
	ContenidoPorCarpeta* contenido;

};
};
};

#endif /* CARPETA_H_ */
