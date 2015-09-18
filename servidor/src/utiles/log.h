#ifndef LOGSINCRONIZADO_H_
#define LOGSINCRONIZADO_H_

// STL
#include <string>
#include <fstream>

class Log
{
private:
	int fd;
	int nivel_log;
	std::string nombre;
	static Log* ptr;

public:

	Log()
	{
		this->fd = open ( this->nombre.c_str(),O_CREAT|O_WRONLY, 0777 );
	}

	~Log(){}

	static void destruir () {
		if ( ptr != NULL ) {
			delete ( ptr );
			ptr = NULL;
		}
	}

	static Log* instancia(){
		if( ptr == NULL )
			ptr = new LogSincronizado();
		return ptr;
	}

	std::string nivelLog(){

		switch(nivel_log)
		{

		}
	}

	void info(const std::string& mensaje, const std::string& autor){
		std::string pid = Tipos::toString(getpid());

		std::string mensaje_completo =
				Tipos::fechaYhora() + " PID: " + pid+" "+ autor +": " + mensaje ;

		//printf(mensaje_completo.c_str());

		archivo_log_info.tomarLockEscritura();

		unsigned int res = archivo_log_info.escribir(static_cast<const void*>(mensaje_completo.c_str()), mensaje_completo.size());

		archivo_log_info.liberarLockEscritura();

		if( res != mensaje_completo.size() ){
			std::string error = "Error al escribir en el log. PID: "+ pid;
			perror(error.c_str());
		}
	}

	void debug(const std::string& mensaje, const std::string& autor){
		std::string pid = Tipos::toString(getpid());

		std::string mensaje_completo =
				Tipos::fechaYhora() + " PID: " + pid+" "+ autor +": " + mensaje ;

		//printf(mensaje_completo.c_str());

		archivo_log_debug.tomarLockEscritura();

		unsigned int res = archivo_log_debug.escribir(static_cast<const void*>(mensaje_completo.c_str()), mensaje_completo.size());

		archivo_log_debug.liberarLockEscritura();

		if( res != mensaje_completo.size() ){
			std::string error = "Error al escribir en el log. PID: "+ pid;
			perror(error.c_str());
		}
	}
};

#endif /* LOGSINCRONIZADO_H_ */
