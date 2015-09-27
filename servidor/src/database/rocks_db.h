#ifndef ROCKS_DB_H_
#define ROCKS_DB_H_
#include <cstdio>
#include <string>
#include <iostream>
#include <assert.h>

#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>


using namespace std;
using namespace rocksdb;


	
class rocks_db{

	public:
		rocks_db();
		virtual ~rocks_db();

		Status open_db();
		Status create_db();
		Status put(string key, string value);
		Status get(string key, string* value); //con  prefijo y sin prefijo
		void delete_db();
		DB* get_db();
		void set_db(DB* db);

	protected:
		
		Options get_options();
		void set_options(Options opt);
		

	private:
		DB* db = NULL;
		Options options;
		string dbpath = "../dbTest";
		Status st;

};	




#endif /* ROCKS_DB_H_ */
