/*
 * Respuesta.h
 *
 *  Created on: 31/10/2015
 *      Author: manuel
 */

#ifndef RESPUESTA_H_
#define RESPUESTA_H_

// entidad
#include "../bd/entidades/EntidadBD.h"

// STL
#include <string>

namespace ConexionServidor
{

class Respuesta : public BaseDeDatos::EntidadDB
{
public:

	enum enumEtiquetas
	{
		ESTADO,
		MENSAJE,
		BYTES
	};

	static const std::string etiquetas[];

	Respuesta();
	virtual ~Respuesta();

	std::string getEstado();
	std::string getMensaje();
	bool getEsDescarga();
	std::string getPathDelArchivoADescargar();

	void setBytes(std::string bytesEnString);
	std::string getBytes();
	void setEstado(std::string estado);
	void setMensaje(std::string mensaje);
	void setEsDescarga(bool);

	void setPathDelArchivoADescargar(std::string);

	// Metodos de EntidadDB
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	virtual std::string getColumnaDeFamilia();
	virtual std::string getClave();

private:

	bool esDescarga;
	std::string pathArchivoADescargar;
};
};

#endif /* RESPUESTA_H_ */
