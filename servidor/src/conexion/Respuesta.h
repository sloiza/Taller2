/// \file Respuesta.h
/// \date 2015-11-26
/// \brief Clase que representa a la respuesta del servidor.
#ifndef RESPUESTA_H_
#define RESPUESTA_H_

// entidad
#include "../bd/entidades/EntidadBD.h"

// STL
#include <string>

namespace ConexionServidor
{
/// \brief Clase que representa a la respuesta del servidor.
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

	/// \brief Constructor.
	Respuesta();
	/// \brief Destructor.
	virtual ~Respuesta();

	/// \brief Devuelve estado de la respuesta.
	std::string getEstado();
	/// \brief Devuelve mensaje de la respuesta.
	std::string getMensaje();
	/// \brief Chequea si es una respuesta de descarga.
	bool getEsDescarga();
	/// \brief Devuelve path del archivo a descarhar.
	std::string getPathDelArchivoADescargar();

	/// \brief Setea bytes.
	void setBytes(std::string bytesEnString);
	/// \brief Devuelve bytes.
	std::string getBytes();
	/// \brief Setea bytes.
	void setEstado(std::string estado);
	/// \brief Setea mensaje.
	void setMensaje(std::string mensaje);
	/// \brief Setea si es una descarga.
	void setEsDescarga(bool);

	/// \brief Setea el path del archivo a descargar.
	void setPathDelArchivoADescargar(std::string);

	// Metodos de EntidadDB
	/// \brief No se usa.
	virtual std::string getValor();

protected:
	// Metodos de EntidadDB
	/// \brief No se usa.
	virtual std::string getColumnaDeFamilia();
	/// \brief No se usa.
	virtual std::string getClave();

private:

	bool esDescarga;
	std::string pathArchivoADescargar;
};
};

#endif /* RESPUESTA_H_ */
