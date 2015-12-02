/// \file Conexion.h
/// \date 2015-11-26
/// \brief Clase que representa a una conexion recibida.
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
/// \brief Clase que representa a una conexion recibida.
class Conexion
{
public:
	/// \brief Constructor.
	Conexion();
	/// \brief Destructor.
	virtual ~Conexion();

	/// \brief Inicializa la conexion, parseando los datos de la conexion.
	void inicializar(struct mg_connection*);
	/// \brief Procesa la request y devuelve una respuesta.
	ConexionServidor::Respuesta procesarRequest();

	/// \brief Devuelve la URI accedida.
	Request::URI* getUri();
	/// \brief Devuelve el metodo utilizado.
	Request::IMetodoREST* getMetodo();
	/// \brief Devuelve el contenido.
	std::string getContenido();
	/// \brief Devuelve la query utilizada.
	std::string getQuery();

	/// \brief Devuelve el contenido en bytes.
	Utiles::Bytes* getContenidoBytes();

	/// \brief Devuelve la impresion de la conexion.
	std::string impresion();

private:
	Request::URI* uri;
	Request::IMetodoREST* metodo;
	std::string contenido;
	std::string query;

	Utiles::Bytes* contenidoBytes;

	std::map<std::string, METODOS>* mapaMetodos;

	/// \brief Parsea el metodo a utilizar.
	Request::IMetodoREST* reconocerMetodo(std::string);
	/// \brief Reconoce y devuelve el contenido.
	std::string reconocerContenido(std::string contenidoTotalDeLaRequestEntera, int contenidoTamanio);
};
};

#endif /* CONEXION_H_ */
