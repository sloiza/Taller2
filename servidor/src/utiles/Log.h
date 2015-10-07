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

	void info(const std::string& mensaje, const std::string& autor);

private:
	std::fstream log;
	static Log* ptr;

};

}

#endif /* LOG_H_ */