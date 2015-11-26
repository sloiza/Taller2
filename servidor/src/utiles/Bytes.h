/// \file Bytes.h
/// \date 2015-11-26
/// \brief Clase para el manejo de una tira de bytes.
#ifndef BYTES_H_
#define BYTES_H_

// utiles
#include "base64.h"

// STL
#include<iostream>
#include <string.h>
#include <vector>

namespace Utiles
{
/// \brief Clase para el manejo de una tira de bytes.
class Bytes {

public:
	/// \brief Constructor.
	Bytes();
	/// \brief Constructor con tamanio fijo.
	Bytes(int tamanio);
	/// \brief Constructor con tira de bytes y tamanio.
	Bytes(char* bytes, int tamanio);
	/// \brief Destructor.
	virtual ~Bytes();

	/// \brief Resetea la tira de bytes poniendoen 0 todos los bytes.
	void resetear();
	/// \brief Libera la memoria ocupada por los char*.
	void liberar();

	/// \brief Setea el vector de bytes.
	void setVectorDeBytes(std::vector<unsigned char>);
	/// \brief Setea una tira de bytes.
	void setBytes(char* bytes);

	/// \brief Devuelve la tira de bytes.
	char* getBytes();
	/// \brief Devuelve el vector de bytes.
	std::vector<unsigned char> getVectorDeBytes();
	/// \brief Devuelve el vector de bytes como un string.
	std::string getStringDeBytes();
	/// \brief Devuelve el vector de bytes codificado en base64.
	std::string getBytesBase64();

	/// \brief Devuelve el tamanio de la tira de bytes.
	int getTamanio();

	/// \brief Imprime los bytes.
	void imprimir();

private:
	std::vector<unsigned char> bytes;
};
};

#endif /* BYTES_H_ */
