/*
 * Bytes.h
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#ifndef BYTES_H_
#define BYTES_H_

// STL
#include<iostream>
#include <string.h>
#include <vector>

namespace Utiles
{

class Bytes {

public:
	Bytes();
	Bytes(int tamanio);
	Bytes(char* bytes, int tamanio);
	virtual ~Bytes();

	void resetear();
	void liberar();

	void setVectorDeBytes(std::vector<unsigned char>);
	void setBytes(char* bytes);

	char* getBytes();
	std::vector<unsigned char> getVectorDeBytes();
	std::string getStringDeBytes();

	int getTamanio();

	void imprimir();

private:
	std::vector<unsigned char> bytes;
};
};

#endif /* BYTES_H_ */
