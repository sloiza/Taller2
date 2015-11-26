
#ifndef CONEXION_H_
#define CONEXION_H_

// Conexion
#include "request/IMetodoREST.h"
#include "request/DELETE.h"
#include "request/GET.h"
#include "request/POST.h"
#include "request/PUT.h"
#include "request/URI.h"
#include "mongoose.h"
#include "Respuesta.h"

// Utiles
#include "../utiles/Log.h"

// Base de datos
#include "../bd/entidades/EntidadBD.h"

// operaciones
#include "../operaciones/CreadorDeOperaciones.h"
#include "../operaciones/IOperable.h"

// STL
#include <string>
#include <map>

namespace ConexionServidor
{

enum METODOS
{
	DELETE,
	GET,
	POST,
	PUT
};

class Conexion
{
public:
	Conexion();
	virtual ~Conexion();

	void inicializar(struct mg_connection*);
	ConexionServidor::Respuesta procesarRequest();

	Request::URI* getUri();
	Request::IMetodoREST* getMetodo();
	std::string getContenido();
	std::string getQuery();

	Utiles::Bytes* getContenidoBytes();

	std::string impresion();

private:
	Request::URI* uri;
	Request::IMetodoREST* metodo;
	std::string contenido;
	std::string query;

	Utiles::Bytes* contenidoBytes;

	std::map<std::string, METODOS>* mapaMetodos;

	Request::IMetodoREST* reconocerMetodo(std::string);
	std::string reconocerContenido(std::string contenidoTotalDeLaRequestEntera, int contenidoTamanio);
};
};

#endif /* CONEXION_H_ */
