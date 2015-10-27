/*
 * Bytes.cpp
 *
 *  Created on: 26/10/2015
 *      Author: manuel
 */

#include "Bytes.h"

using namespace Utiles;

Bytes::Bytes() : bytes(0) {}

Bytes::Bytes(int tamanio) : bytes(tamanio) {}

Bytes::Bytes(char* bytes, int tamanio) : bytes(tamanio)
{
	this->setBytes(bytes);
}

Bytes::~Bytes()
{
	this->liberar();
}

void Bytes::resetear()
{
	memset(&this->bytes[0], 0, this->bytes.size());
}

void Bytes::setVectorDeBytes(std::vector<unsigned char> bytes)
{
	this->bytes = bytes;
}

void Bytes::setBytes(char* bytes)
{
	this->resetear();
	memcpy(&this->bytes[0], bytes, this->bytes.size());
}

char* Bytes::getBytes()
{
	return (char*)&this->bytes[0];
}

std::vector<unsigned char> Bytes::getVectorDeBytes()
{
	return this->bytes;
}

std::string Bytes::getStringDeBytes()
{
	std::string stringDeBytes(this->bytes.begin(), this->bytes.end());
	return stringDeBytes;
}

int Bytes::getTamanio()
{
	return this->bytes.size();
}

void Bytes::liberar()
{
	this->bytes.clear();
}

void Bytes::imprimir()
{
	std::cout << this->getTamanio() << " bytes: " << this->getBytes();
}
