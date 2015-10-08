#ifndef USER_H_
#define USER_H_
#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "../utiles/utiles.h"
#include "../database/rocks_db.h"



using namespace std;
using namespace Utiles;
using namespace rocksdb;
	
class User{

	public:
			
		User();
		User(string firstName, string lastName, string nickName, string email, string pathProf,string location);
		virtual ~User();
		string getName();
		void setName(string name);
		string getLastName();
		void setLastName(string lastName);
		string getEmail();
		void setEmail(string email);
		string getProfilePhoto();
		void setProfilePhoto(string pathProf);
		string getLocation();
		void setLocation(string location);
		string getNickName();
		void setNickName(string nickName);
		double getID();
		string toJson();
		void fromJson(string json);
		void setStatus(bool st);
		bool getStatus();
		Status get(Slice key, string* value);
		Status add(rocks_db* rocks);
		Status signIn();
		Status signUp();
		
	private:
		string firstName;
		bool status;
		string lastName;
		string nickName;
		string email;
		string pathProf;
		string location;
		double id; //id static o key para buscar en rocks VER
		string colName;

		
};	
	



#endif /* USER_H_ */
