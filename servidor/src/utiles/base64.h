#include <string>

/// \brief Devuelve el string codificado en base64.
std::string base64_encode(unsigned char const* , unsigned int len);
/// \brief Decodificado un string en base64 y lo devuelve.
std::string base64_decode(std::string const& s);
