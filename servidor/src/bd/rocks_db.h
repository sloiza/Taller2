#ifndef ROCKS_DB_H_
#define ROCKS_DB_H_
#include <cstdio>
#include <string>
#include <iostream>
#include <assert.h>
#include <vector>

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
		Status put(string column, Slice key, Slice value);
		Status get(string column, Slice key, string* value); //con  prefijo y sin prefijo
		Status delet(string column, Slice key);
		void delete_db();
		DB* get_db();
		void set_db(DB* db);

		//struct que tiene el id en el vector del handler de column families
		struct CF_id{
			int def = 0;
			int user = 1;
			int file = 2;
		};

	protected:
		
		string CF_name[3] = {kDefaultColumnFamilyName, "user", "file"};
		int cantCFs();



	private:
		DB* db = NULL;
		Options options;
		string dbpath = "rocksDB";
		Status st;
		vector<ColumnFamilyDescriptor> column_families;
		vector<ColumnFamilyHandle*> handles;
		void createCF(DB* db);
		void createCFDescriptor();
		int getIdCF(string column);

};	




#endif /* ROCKS_DB_H_ */
