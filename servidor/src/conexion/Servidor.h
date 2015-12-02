/// \file Servidor.h
/// \date 2015-11-26
/// \brief Clase que corre y detiene el servidor.
#ifndef SERVIDOR_H_
#define SERVIDOR_H_

// STL
#include <iostream>
#include <signal.h>

// Conexion
#include "HandlerEventos.h"
#include "mongoose.h"
#include "../utiles/utiles.h"

// operaciones
#include "../operaciones/CreadorDeOperaciones.h"

namespace ConexionServidor
{
/// \brief Clase que corre y detiene el servidor.
class Servidor
{

public:
	/// \brief Constructor.
	Servidor();
	/// \brief Destructor.
	virtual ~Servidor();

	/// \brief Crea al servidor.
	void crear();
	/// \brief Crea al servidor con el puerto.
	void crear(int puerto);
	/// \brief Setea el puerto.
	void setPuerto(int);
	/// \brief Setea opcion de mongoose.
	void setOpcion(std::string nombre, std::string valor);
	/// \brief Escucha requests.
	int escuchar(int);
	/// \brief Chequea si esta corriendo el servidor.
	bool estaCorriendo();
	/// \brief Cierra el servidor.
	void destruir();

protected:
	/// \brief Reconoce la SIGNINT que detiene al servidor.
	static void handlerSenial(int);

private:
	struct mg_server* servidorMG;
	int puerto;
	HandlerEventos handler;
	static bool corriendo;
};

};

#endif /* SERVIDOR_H_ */
