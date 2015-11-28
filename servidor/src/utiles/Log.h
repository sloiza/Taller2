/*
 * Log.h
 *
 *  Created on: 28/9/2015
 *      Author: manuel
 */

#ifndef LOG_H_
#define LOG_H_

// STL
#include <string>
#include <fstream>

// Utiles
#include "utiles.h"

namespace Utiles
{

class Log {
public:
	Log();
	virtual ~Log();

	static Log* instancia();
	static void destruir();

	static void info(const std::string& mensaje, const std::string& autor);
	static void error(const std::string& mensaje, const std::string& autor);
	static void warn(const std::string& mensaje, const std::string& autor);
	static void debug(const std::string& mensaje, const std::string& autor);
	static void trace(const std::string& mensaje, const std::string& autor);

private:
	static std::fstream logInfo;
	static std::fstream logError;
	static std::fstream logWarn;
	static std::fstream logDebug;
	static std::fstream logTrace;
	static Log* ptr;

};

}

#endif /* LOG_H_ */
