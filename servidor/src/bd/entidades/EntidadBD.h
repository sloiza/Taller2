
#ifndef ENTIDAD_H_
#define ENTIDAD_H_

// Base de datos
#include "../ClaveRocksDB.h"
#include "../ManagerBD.h"
#include "../JsonInfo.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{
	/**
	 * @brief Clase utilizada por las entidades para interactuar con la base de datos
	 */
class EntidadDB {
public:
	EntidadDB();
	virtual ~EntidadDB();
	/**
	 * @brief Setea un json al json de la entidad
	 */
	void setContenido(JsonInfo* contenido);
	/**
	 * @brief Setea un string al json de la entidad
	 */
	void setContenido(std::string contenido);
	virtual std::string getContenido();
	/**
	 * @brief Valida si el contenido del json de la entidad es válido.
	 */
	bool contenidoValido();
	/**
	 * @brief Obtiene la clave de la entidad.
	 */
	virtual ClaveRocksDB getClaveRocksDB();
	/**
	 * @brief Obtiene de la entidad el valor.
	 */
	virtual std::string getValor() = 0;
	/**
	 * @brief Obtiene de la entidad la clave y el valor a insertar, y lo guarda en base de datos
	 */
	virtual void guardar(); 		// PUT
	/**
	 * @brief Obtiene de la entidad el nuevo valor a insertar, y lo guarda en base de datos
	 */
	virtual void modificar(); 	// POST
	/**
	 * @brief Elimina de base de datos la clave y los datos asociados a la entidad
	 */
	virtual void eliminar(); 	// DELETE
	/**
	 * @brief Obtiene de base de datos los datos asociados a la entidad
	 */
	virtual std::string recuperar(); 	// GET

protected:
	virtual std::string getColumnaDeFamilia() = 0;
	virtual std::string getClave() = 0;

	JsonInfo* info;
};
};
};

#endif /* ENTIDAD_H_ */
