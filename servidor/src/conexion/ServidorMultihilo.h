
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

class ServidorMultihilo
{
public:

	ServidorMultihilo();
	virtual ~ServidorMultihilo();

	void crear();
	void setNumeroDeHilos(int);
	void setPuerto(int);
	void setOpcion(std::string nombre, std::string valor);
	static void* servir(void *server);
	void comenzarAEscuchar();
	bool estaCorriendo();
	void destruir();

	std::string nombreClase();

protected:
	static void handlerSenial(int);

private:
	std::vector<struct mg_server*> servidores;
	int puerto;
	HandlerEventos handler;
	static bool corriendo;

};
};

#endif /* SERVIDORMULTIHILO_H_ */
