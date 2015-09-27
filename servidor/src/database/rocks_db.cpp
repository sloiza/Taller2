#include "rocks_db.h"

//using namespace rocks_db;
using namespace rocksdb;

rocks_db::rocks_db(){
	Status s = this->create_db();
	if(s.ok()){
		this->open_db();
	}else{
		//ya fue creada, s´olo se abre
		cerr << s.ToString() << endl;
		this->open_db();
	}
	
}
Status rocks_db::create_db(){
	Status s;
 	Options options;
	DB* _db;
	options.error_if_exists = true;
	options.create_if_missing = true;
	s = DB::Open(options, this->dbpath, &_db);
	if(s.ok()){
		cout << "DB created \n";

	}
	delete _db;
	return s;
 }

Status rocks_db::open_db(){
	Status s;
 	Options options ;
	DB* _db = this->get_db();;
	s = DB::Open(options, this->dbpath, &_db);
	printf("db pointer open %p\n", _db);
	if(s.ok()){
		this->set_db(_db);
		cout << "DB opened \n";

	}else{
		cout << "DB couldn't be opened. DB Error " ;
		cerr << s.ToString() << endl;
	}

	return s;
}

Options rocks_db::get_options(){
	return this->options;
}

void rocks_db::set_options(Options opt){
	this->options = opt;
}

Status rocks_db::put(string key, string value){
	DB* db = this->get_db();
	cout << "db pointer put \n";
	printf("%p\n", db);
	Status s = db->Put(WriteOptions(), key , value);
	return s;
}

Status rocks_db::get(string key, string* value){
	DB* db = this->get_db();
	cout << "DB pointer get \n";
	printf("%p\n", db);
	Status s = db->Get(ReadOptions(), key, value);
	cout << "valor: "<< *value << "\n";
	return s;

}

rocks_db::~rocks_db()
{
	if(this->db != NULL){
		cout << "closing db " << endl;
		delete this->db;		
	}
}

DB* rocks_db::get_db(){
	return this->db;
}

void rocks_db::set_db(DB* db){
	this->db = db;;
}
