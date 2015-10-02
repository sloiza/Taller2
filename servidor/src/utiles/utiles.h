/*
 * tipos.h
 *
 *  Created on: 28/4/2015
 *      Author: manuel
 */

#ifndef UTILES_H_
#define UTILES_H_

// STL
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;




namespace Utiles
{
	static std::string toString(int i){
		std::stringstream ss;
		ss << i;
		return ss.str();
	}

	static int toInt(std::string s){
		return atoi(s.c_str());
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

	static vector<string> split(string str, char sep){

		vector<string> vect;
		stringstream ss(str);
		
		while (ss.good())
		{
			string substr;
			getline( ss, substr, sep);
		    vect.push_back(substr);
		}
		return vect;
		
	}

	// string getHashValue(void* obj){

	// }
};



#endif /* UTILES_H_ */
