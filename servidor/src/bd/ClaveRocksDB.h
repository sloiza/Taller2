#ifndef CLAVEROCKSDB_H_
#define CLAVEROCKSDB_H_

// STL
#include <string>

namespace ConexionServidor
{

namespace BaseDeDatos
{
	/**
	 * @brief Estructura utilizada para las claves de la base de datos,
	 * la misma contiene el nombre de la columna a la que pertenece y
	 * el valor de la misma
	 */
struct ClaveRocksDB
{
	std::string columna;
	std::string clave;
};
};
};

#endif /* CLAVEROCKSDB_H_ */
