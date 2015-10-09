#include "rocks_db.h"

//using namespace rocks_db;
using namespace rocksdb;

rocks_db::rocks_db(){
	Status s = this->create_db();
	if(s.ok()){
		cout << "open OK" << endl;
		this->open_db();
	}else{
		//ya fue creada, s´olo se abre
		cerr << s.ToString() << endl;
		cout << "only open" << endl;
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
		this->createCF(_db);
		cout << "DB created \n";
		//this->handles = handles;

	}else{
		cout << "DB couldn't be created. DB Error " ;
		cerr << s.ToString() << endl;	
	}
	delete _db;
	return s;
 }

void rocks_db::createCF(DB* db){
	int i;
	Status s;
	for(i = 0; i< this->cantCFs(); i++){
		ColumnFamilyHandle* cf = NULL;
  		s = db->CreateColumnFamily(ColumnFamilyOptions(), this->CF_name[i], &cf);
  		if(s.ok()){
  			cout << "Created column OK "<< endl;
  		}else{
  			cerr << s.ToString() << endl;
  		}
  		delete cf;
	}
}


void rocks_db::createCFDescriptor(){
	int i;
	vector<ColumnFamilyDescriptor> column_families;
	for(i = 0; i< this->cantCFs(); i++){
		column_families.push_back(ColumnFamilyDescriptor(this->CF_name[i], ColumnFamilyOptions()));
	}
	this->column_families = column_families;
	
}
		



Status rocks_db::open_db(){
	Status s;
 	Options options ;
	DB* _db = this->get_db();
	//this->createCF();
	this->createCFDescriptor();

	vector<ColumnFamilyHandle*> handles;
	s = DB::Open(options, this->dbpath, this->column_families, &handles, &_db);
	//s = DB::Open(options, this->dbpath, &_db);
	if(s.ok()){
		this->set_db(_db);
		cout << "DB opened \n";
		this->handles = handles;

	}else{
		cout << "DB couldn't be opened. DB Error " ;
		cerr << s.ToString() << endl;
	}

	return s;
}

int rocks_db::cantCFs(){
	return sizeof(this->CF_name)/sizeof(this->CF_name[0]);
}


Options rocks_db::get_options(){
	return this->options;
}

void rocks_db::set_options(Options opt){
	this->options = opt;
}

Status rocks_db::put(string column, Slice key, Slice value){
	DB* db = this->get_db();
	int id  = this->getIdCF(column);
	//printf("%p\n", db);
	Status s = db->Put(WriteOptions(), this->handles[id], key , value);
	if(s.ok()){
		cout << "Put OK" << endl;
		return s;
	}else{
		cout << "Failed insert in db. DB Error" << endl;
		cerr << s.ToString() << endl;
		return s;
	}
}

Status rocks_db::get(string column, Slice key, string* value){
	DB* db = this->get_db();
	int id = this->getIdCF(column);
	Status s = db->Get(ReadOptions(), this->handles[id], key, value);
	if(s.ok()){
		cout << "Get OK: "<< *value << "\n";
	}else{
		cerr << "DB Error " << s.ToString() << endl;
	}
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

//deprecated
void rocks_db::iterate_db(){
	Iterator* it = this->db->NewIterator(ReadOptions());
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		cout << it->key().ToString() << ": " << it->value().ToString() << endl;
	}
	delete it;
}

//deprecated
void rocks_db::search(Slice prefix){
 	auto iter = this->db->NewIterator(ReadOptions());
    for (iter->Seek(prefix); iter->Valid() && iter->key().starts_with(prefix); iter->Next()) {
		cout << iter->key().ToString() << ": " << iter->value().ToString() << endl;
    }
}
int rocks_db::getIdCF(string name){
	
	if(strcmp(name.c_str(), this->CF_name[0].c_str()) == 0){
		return 0;
	}else if(strcmp(name.c_str(), this->CF_name[1].c_str()) == 0){
		return 1;
	}else if(strcmp(name.c_str(), this->CF_name[2].c_str()) == 0){
		return 2;
	}
		

}

void rocks_db::ListColumnFamilies(){
	// Status s= this->db->ListColumnFamilies(this->options, this->dbpath, this->column_families);
	// for (vector<int>::iterator it = this->column_families.begin() ; it != this->column_families.end(); ++it){
	// 	cout << ' ' << *it << endl;
		
	// }

}
