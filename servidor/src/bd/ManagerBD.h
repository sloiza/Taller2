#ifndef MANAGERBD_H_
#define MANAGERBD_H_

// Base de datos
#include "ClaveRocksDB.h"
#include "rocks_db.h"

namespace ConexionServidor
{
namespace BaseDeDatos
{

class ManagerBD {
public:
	ManagerBD();
	virtual ~ManagerBD();
	/**
	 * @brief Inicializa la base de datos
	 */
	static void inicializar();
	/**
	 * @brief Valida si la base de datos está inicializada
	 */
	static bool estaAbierta();
	/**
	 * @brief Cierra la base de datos
	 */
	static void cerrar();
	/**
	 * @brief Inserta en base de datos
	 * @param clave [ClaveRocksDB contiene nombre de columna y clave a insertar]
	 * @param valor
	 */
	static void insertar(ClaveRocksDB clave, std::string valor);
	/**
	 * @brief Elimina de base de datos
	 * @param clave [ClaveRocksDB contiene nombre de columna y clave a eliminar]
	 */
	static void eliminar(ClaveRocksDB clave);
	/**
	 * @brief Busca en base de datos
	 * @param clave [ClaveRocksDB contiene nombre de columna y clave a buscar]
	 * @return Valor obtenido de base de datos
	 */
	static std::string recuperar(ClaveRocksDB clave);

private:
	static rocks_db* db;
};
};
};

#endif /* MANAGERBD_H_ */
