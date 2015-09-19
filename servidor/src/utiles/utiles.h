/*
 * tipos.h
 *
 *  Created on: 28/4/2015
 *      Author: manuel
 */

#ifndef TIPOS_H_
#define TIPOS_H_

#include <string>
#include <sstream>

namespace Utiles
{
	static std::string toString(int i){
		std::stringstream ss;
		ss << i;
		return ss.str();
	}

	static std::string fechaYhora(){
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];

		time (&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
		std::string str(buffer);
		return str;
	}

	enum niveles { DEBUG, AVISO, INFO, ERROR };
};



#endif /* TIPOS_H_ */
