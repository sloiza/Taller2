/// \file utiles.h
/// \date 2015-11-26
/// \brief Clase que contiene metodos utiles.
#ifndef UTILES_H_
#define UTILES_H_

// STL
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <vector>

namespace Utiles
{
/// \brief Clase que contiene metodos utiles.
class Metodos
{
public:
	/// \brief Duelve un 'int' como 'string'.
	static std::string toString(int i){
		std::stringstream ss;
		ss << i;
		return ss.str();
	}

	/// \brief Duelve un 'string' como 'int'.
	static int toInt(std::string s){
		return atoi(s.c_str());
	}

	/// \brief Duelve la fecha y la hora
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

	/// \brief Imprime por pantalla la ayuda de usuario.
	static void imprimirAyuda()
	{
		std::fstream archivo;
		archivo.open("../ayuda.txt");
		if( !archivo.is_open() )
		{
			std::cout << "No se encontro el texto de ayuda \"ayuda.txt\".\n";
		}
		std::cout << archivo.rdbuf();
	}

	/// \brief Divide un string en partes, partiendolo segun el separador indicado.
	static std::vector<std::string> split(std::string str, char sep){

		std::vector<std::string> vect;
		std::stringstream ss(str);

		while (ss.good())
		{
			std::string substr;
			getline( ss, substr, sep);
		    vect.push_back(substr);
		}
		return vect;
	}
};
};



#endif /* UTILES_H_ */
