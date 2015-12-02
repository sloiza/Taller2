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
	static void info(const std::string& mensaje, const std::string& autor);
	/// \brief Loggea en el log de errores.
	static void error(const std::string& mensaje, const std::string& autor);
	/// \brief Loggea en el log de adventencias.
	static void warn(const std::string& mensaje, const std::string& autor);
	/// \brief Loggea en el log de debug.
	static void debug(const std::string& mensaje, const std::string& autor);
	/// \brief Loggea en el log de trazabilidad.
	static void trace(const std::string& mensaje, const std::string& autor);

private:
	static std::fstream logInfo;
	static std::fstream logError;
	static std::fstream logWarn;
	static std::fstream logDebug;
	static std::fstream logTrace;
	static Log* ptr;

};

};

#endif /* LOG_H_ */
