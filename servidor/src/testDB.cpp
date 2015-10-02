#include "database/rocks_db.h"
#include "clases/User.h"
//#include "utiles/LectorParametros.h"
#include "utiles/utiles.h"
using namespace Utiles;

namespace test{
  int test_db() {
    rocks_db* rocks = new rocks_db();
    //User* us = new User();
    cout << "After create " << endl;
    // DB* db = rocks->get_db();
    cout << "paso  \n";
    Status s;
    // Put key-value
    s = rocks->put("user",Slice("key1"),"apolo");
    assert(s.ok());
    cout << "INSERT \n";
    string value;
    // get value
    s = rocks->get("user",Slice("key1"), &value);
    assert(s.ok());
    cout << "valor " <<value << endl;
    assert(value == "apolo");
    printf("%s \n",value.c_str());
    cout << "LEYO, delete rocks "<< endl;
    delete rocks;
    printf(" db pointer after %p\n", rocks);

    return 0;

  }

  void testUser(){
  	User* user = new User("Samanta", "Loiza", "sami", "samiloiza@gmail.com", "/path/to/file", "Argentina");
  	cout << user->toJson() << endl;
    rocks_db* rocks = new rocks_db();
    Status s;
    // Put key-value
    s = rocks->put("user", Slice("1"),user->getName());
    s = rocks->put("user", Slice("2"),user->toJson());
    s = rocks->put("file", Slice("2"),"user->toJson()FS");
    s = rocks->put("file", Slice("cat_2"),"user->toJson()");
    if(s.ok()){
    }

     string value1, value2;
    // get value
    //s = user->get(Slice("2"), &value1);
    s = rocks->get("user", Slice("2"), &value1);
    printf("VALUE1 : %s \n",value1.c_str());
     s = rocks->get("file", Slice("2"), &value2);
    printf("VALUE2 : %s \n",value2.c_str());





   

   // rocks->iterate_db();
    // cout << "Only user " << endl;
    // rocks->search(Slice("user"));
    // cout << "Only file " << endl;
    // rocks->search(Slice("file"));

    //std::string str = "1,2,3,4,5,6";
    //string sep = string(",");
    

   




  }
}
