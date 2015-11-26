/// \file ServidorMultihilo.h
/// \date 2015-11-26
/// \brief Clase que corre y detiene el servidor multihilo.
#ifndef SERVIDORMULTIHILO_H_
#define SERVIDORMULTIHILO_H_

// Conexion
#include "HandlerEventos.h"
#include "mongoose.h"
#include "../utiles/utiles.h"

// operaciones
#include "../operaciones/CreadorDeOperaciones.h"

// STL
#include <iostream>
#include <signal.h>

namespace ConexionServidor
{
/// \brief Clase que corre y detiene el servidor multihilo.
class ServidorMultihilo
{
public:
	/// \brief Constructor.
	ServidorMultihilo();
	/// \brief Destructor.
	virtual ~ServidorMultihilo();

	/// \brief Crea al servidor.
	void crear();
	/// \brief Setea el numero de hilos.
	void setNumeroDeHilos(int);
	/// \brief Setea el puerto.
	void setPuerto(int);
	/// \brief Setea opcion de mongoose.
	void setOpcion(std::string nombre, std::string valor);
	/// \brief Funcion que se le pasa los hilos que corren los servidores.
	static void* servir(void *server);
	/// \brief Pone a escuchar a los hilos.
	void comenzarAEscuchar();
	/// \brief Chequea si esta corriendo el servidor.
	bool estaCorriendo();
	/// \brief Cierra el servidor.
	void destruir();

	/// \brief Devuelve el nombre de la clase.
	std::string nombreClase();

protected:
	/// \brief Reconoce la SIGNINT que detiene al servidor.
	static void handlerSenial(int);

private:
	std::vector<struct mg_server*> servidores;
	int puerto;
	HandlerEventos handler;
	static bool corriendo;

};
};

#endif /* SERVIDORMULTIHILO_H_ */
