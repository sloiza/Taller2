/// \file Log.h
/// \date 2015-11-26
/// \brief Logger del servidor.
#ifndef LOG_H_
#define LOG_H_

// STL
#include <string>
#include <fstream>

// Utiles
#include "utiles.h"

namespace Utiles
{
/// \brief Logger del servidor.
class Log
{
public:
	/// \brief Constructor.
	Log();
	/// \brief Destructor.
	virtual ~Log();

	/// \brief Devuelve la instancia del Log.
	static Log* instancia();
	/// \brief Cierra y libera el log.
	static void destruir();

	/// \brief Loggea en el log de informacion.
	void info(const std::string& mensaje, const std::string& autor);
	/// \brief Loggea en el log de errores.
	void error(const std::string& mensaje, const std::string& autor);
	/// \brief Loggea en el log de adventencias.
	void warn(const std::string& mensaje, const std::string& autor);
	/// \brief Loggea en el log de debug.
	void debug(const std::string& mensaje, const std::string& autor);
	/// \brief Loggea en el log de trazabilidad.
	void trace(const std::string& mensaje, const std::string& autor);

private:
	std::fstream logInfo;
	std::fstream logError;
	std::fstream logWarn;
	std::fstream logDebug;
	std::fstream logTrace;
	static Log* ptr;

};

};

#endif /* LOG_H_ */
