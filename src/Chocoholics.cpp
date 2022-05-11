#include "Provider.h"
#include "sqlite3.h"
#include <cstring>

using namespace std;

Chocoholics::Chocoholics() {
    path = "DATA.db";
    createTable();
}

 void Chocoholics::createTable() {
    sqlite3* DB;
    char* messageError;
    sqlite3_open(path.c_str(), &DB);

    //creatse table for Providers and Members
    string query = "CREATE TABLE IF NOT EXISTS USERS ("
	"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
	"USER_NAME TEXT NOT NULL, "
	"STREET TEXT NOT NULL, "
    "CITY TEXT NOT NULL, "
    "STATE TEXT NOT NULL, "
    "ZIP_CODE INTEGER);";
    try {
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		int exit = sqlite3_exec(DB, query.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error in createTable function: "<<messageError<< endl;
			sqlite3_free(messageError);
		}

	} catch (const exception& e) {
		cerr << e.what();
	}


    //creates table service list for providers and members
    string query1 = "CREATE TABLE IF NOT EXISTS SERVICES ("
    "PARENT_ID INTEGER, "
    "ID INTERGER, "
    "USER_NAME TEXT NOT NULL, "
    "MONTH INTEGER, "
    "DAY INTEGER, "
    "YEAR INTEGER, "
    "COMP_TIME INTEGER, "
    "SERVICE_NAME TEXT NOT NULL, "
    "SERVICE_CODE INTEGER, "
    "FEE INTEGER, "
    "COMMENT TEXT, "
    "TABLE_KEY INTEGER PRIMARY KEY, "
    "UNIQUE (TABLE_KEY), "
    "FOREIGN KEY (PARENT_ID) REFERENCES USERS(ID));";
    try {
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		int exit = sqlite3_exec(DB, query1.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error : createTable : "<<messageError<< endl;
			sqlite3_free(messageError);
		}

	} catch (const exception& e) {
		cerr << e.what();
	}


    //creates tables for directory list
    string query2 = "CREATE TABLE IF NOT EXISTS DIRECTORY ("
    "SERVICE_NUMBER INTEGER PRIMARY KEY, "
    "SERVICE_NAME TEXT NOT NULL, "
    "BILL INTEGER);";
    try {
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		int exit = sqlite3_exec(DB, query2.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error : createTable : "<<messageError<< endl;
			sqlite3_free(messageError);
		}

	} catch (const exception& e) {
		cerr << e.what();
	}

    sqlite3_close(DB);
 }

 int Chocoholics::insertMember(Member*& mem) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);

    string q = "PRAGMA foreign_keys = ON;";
    int exit = sqlite3_exec(DB, q.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : insertData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}
    string q1 = "INSERT OR REPLACE INTO USERS ('ID', 'USER_NAME', 'STREET', 'CITY', 'STATE','ZIP_CODE') VALUES (";
    q1 += "'"; q1 += to_string(mem->getId()); q1 += "', ";
    q1 += "'"; q1 += mem->getUserName(); q1 += "', ";
    q1 += "'"; q1 += mem->getStreet(); q1 += "', ";
    q1 += "'"; q1 += mem->getCity(); q1 += "', ";
    q1 += "'"; q1 += mem->getState(); q1 += "', ";
    q1 += "'"; q1 += to_string(mem->getZipCode()); q1 += "')";
    

	exit = sqlite3_exec(DB, q1.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : insertData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}
    

    vector <Service*> ser = mem->getAllService();

    for (auto i : ser) {
        string q2 = "INSERT OR REPLACE INTO SERVICES ('PARENT_ID', 'ID', 'USER_NAME', 'MONTH', 'DAY', 'YEAR', 'COMP_TIME', 'SERVICE_NAME', 'SERVICE_CODE', 'FEE', 'COMMENT') VALUES (";
        q2 +="'"; q2 += to_string(mem->getId()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getId()); q2 +="', ";
        q2 +="'"; q2 += i->getUserName(); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getMonth()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getDay()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getYear()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getCompTime()); q2 +="', ";
        q2 +="'"; q2 += i->getServiceName(); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getServiceNumber()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getFee()); q2 +="', ";
        q2 +="'"; q2 += i->getComment(); q2 +="'); ";
        


        exit = sqlite3_exec(DB, q2.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error : insertData : "<<messageError<< endl;
            sqlite3_free(messageError);
            sqlite3_close(DB);
            return 1;
        }

    }
    sqlite3_close(DB);

    return 0;
}


int Chocoholics::selectMember(const int key, Member*& mem) {

    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);

    string query= "SELECT * FROM USERS WHERE ID = ";
    query += to_string(key);
    mem = new Member;

    int exit = sqlite3_exec(DB, query.c_str(), callbackMem, mem, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : selectData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	};

    if (mem->getUserName().size() == 0) {
        delete mem;
        mem = NULL;
        sqlite3_close(DB);
        return 2;
    }

    string q1 = "SELECT * FROM SERVICES WHERE PARENT_ID = ";
    q1 += to_string(mem->getId());

    exit = sqlite3_exec(DB, q1.c_str(), callbackServiceMem, &mem->getAllService(), &messageError);

	if (exit != SQLITE_OK) {
		cerr << "Error : selectData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}

    sqlite3_close(DB);
    return 0;
}


int Chocoholics::callbackMem(void* mem, int argc, char** argv, char** azColName){
	for (int i = 0; i < argc; i++) {
		// column name and value
        callbackMemApp(mem, argv[i], azColName[i]);
	}
	return 0;
}
void Chocoholics::callbackMemApp(void* mem, char* argv, char* azColName) {
    Member* ptr = reinterpret_cast<Member*> (mem);
    if (strcmp(azColName, "ID") == 0 ) ptr -> updateId(atoi(argv));
    if (strcmp(azColName, "USER_NAME") == 0 ) ptr -> updateUserName(argv);
    if (strcmp(azColName, "STREET") == 0 ) ptr -> updateStreet(argv);
    if (strcmp(azColName, "CITY") == 0 ) ptr -> updateCity(argv);
    if (strcmp(azColName, "STATE") == 0 ) ptr -> updateState(argv);
    if (strcmp(azColName, "ZIP_CODE") == 0 ) ptr -> updateZipCode(atoi(argv));
}

int Chocoholics::callbackServiceMem(void* ser, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        // cout << azColName[i] << ": " << argv[i] << endl;
        callbackServiceMemApp(ser, argv[i], azColName[i], i);
    }
    return 0;
}


void Chocoholics::callbackServiceMemApp(void* ser, char* argv, char* azColName, int i) {
    vector <Service*>* ptr = reinterpret_cast<vector <Service*>*> (ser);
    if (i % 12 == 0) {
        Service* ser = new Service();
        ptr->push_back(ser);
    }
    int arr = ptr->size() - 1;

    if (strcmp(azColName, "ID") == 0) ptr->operator[](arr)->updateId(atoi(argv));
    if (strcmp(azColName, "USER_NAME") == 0) ptr->operator[](arr)->updateUserName(argv);
    if (strcmp(azColName, "MONTH") == 0) ptr->operator[](arr)->updateMonth(atoi(argv));
    if (strcmp(azColName, "DAY") == 0) ptr->operator[](arr)->updateDay(atoi(argv));
    if (strcmp(azColName, "YEAR") == 0) ptr->operator[](arr)->updateYear(atoi(argv));
    if (strcmp(azColName, "COMP_TIME") == 0) ptr->operator[](arr)->updateCompTime(atoi(argv));
    if (strcmp(azColName, "SERVICE_NAME") == 0) ptr->operator[](arr)->updateServiceName(argv);
    if (strcmp(azColName, "SERVICE_CODE") == 0) ptr->operator[](arr)->updateServiceNum(atoi(argv));
    if (strcmp(azColName, "FEE") == 0) ptr->operator[](arr)->updateFee(atoi(argv));
    if (strcmp(azColName, "COMMENT") == 0) ptr->operator[](arr)->updateComment(argv);
}




 int Chocoholics::insertProvider(Provider*& mem) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);

    string q = "PRAGMA foreign_keys = ON;";
    int exit = sqlite3_exec(DB, q.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : insertData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	};

    string q1 = "INSERT OR REPLACE INTO USERS ('ID', 'USER_NAME', 'STREET', 'CITY', 'STATE','ZIP_CODE') VALUES (";
    q1 += "'"; q1 += to_string(mem->getId()); q1 += "', ";
    q1 += "'"; q1 += mem->getUserName(); q1 += "', ";
    q1 += "'"; q1 += mem->getStreet(); q1 += "', ";
    q1 += "'"; q1 += mem->getCity(); q1 += "', ";
    q1 += "'"; q1 += mem->getState(); q1 += "', ";
    q1 += "'"; q1 += to_string(mem->getZipCode()); q1 += "')";
    

	exit = sqlite3_exec(DB, q1.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : insertData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}
    

    vector <Service*> ser = mem->getAllService();

    for (auto i : ser) {
        string q2 = "INSERT OR REPLACE INTO SERVICES ('PARENT_ID', 'ID', 'USER_NAME', 'MONTH', 'DAY', 'YEAR', 'COMP_TIME', 'SERVICE_NAME', 'SERVICE_CODE', 'FEE', 'COMMENT') VALUES (";
        q2 +="'"; q2 += to_string(mem->getId()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getId()); q2 +="', ";
        q2 +="'"; q2 += i->getUserName(); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getMonth()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getDay()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getYear()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getCompTime()); q2 +="', ";
        q2 +="'"; q2 += i->getServiceName(); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getServiceNumber()); q2 +="', ";
        q2 +="'"; q2 += to_string(i->getFee()); q2 +="', ";
        q2 +="'"; q2 += i->getComment(); q2 +="'); ";
        


    exit = sqlite3_exec(DB, q2.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : insertData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}

    }

    sqlite3_close(DB);
    return 0;
}



int Chocoholics::selectProvider(const int key, Provider*& pro) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);

    string query= "SELECT * FROM USERS WHERE ID = ";
    query += to_string(key);

    pro = new Provider;

    int exit = sqlite3_exec(DB, query.c_str(), callbackPro, pro, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : selectData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}
    if (pro->getUserName().size() == 0) {
        delete pro;
        pro = NULL;
        sqlite3_close(DB);
        return 2;
    }

    string q1 = "SELECT * FROM SERVICES WHERE PARENT_ID = ";
    q1 += to_string(pro->getId());
    
    exit = sqlite3_exec(DB, q1.c_str(), callbackServiceMem, &pro->getAllService(), &messageError);

	if (exit != SQLITE_OK) {
		cerr << "Error : selectData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}
    
    sqlite3_close(DB);
    return 0;
}


int Chocoholics::callbackPro(void* pro, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
		// column name and value
        callbackProApp(pro, argv[i], azColName[i]);
	}
	return 0;
}


void Chocoholics::callbackProApp(void* pro, char* argv, char* azColName) {
    Provider* ptr = reinterpret_cast<Provider*> (pro);
    if (strcmp(azColName, "ID") == 0 ) ptr -> updateId(atoi(argv));
    if (strcmp(azColName, "USER_NAME") == 0 ) ptr -> updateUserName(argv);
    if (strcmp(azColName, "STREET") == 0 ) ptr -> updateStreet(argv);
    if (strcmp(azColName, "CITY") == 0 ) ptr -> updateCity(argv);
    if (strcmp(azColName, "STATE") == 0 ) ptr -> updateState(argv);
    if (strcmp(azColName, "ZIP_CODE") == 0 ) ptr -> updateZipCode(atoi(argv));
}

int Chocoholics::callbackServicePro(void* ser, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
            // cout << azColName[i] << ": " << argv[i] << endl;
            callbackServiceProApp(ser, argv[i], azColName[i], i);
        }
        return 0;
}

void Chocoholics::callbackServiceProApp(void* ser, char* argv, char* azColName, int i) {
    vector <Service*>* ptr = reinterpret_cast<vector <Service*>*> (ser);
    if (i % 12 == 0) {
        Service* ser = new Service();
        ptr->push_back(ser);
    }
    int arr = ptr->size() - 1;

    if (strcmp(azColName, "ID") == 0) ptr->operator[](arr)->updateId(atoi(argv));
    if (strcmp(azColName, "USER_NAME") == 0) ptr->operator[](arr)->updateUserName(argv);
    if (strcmp(azColName, "MONTH") == 0) ptr->operator[](arr)->updateMonth(atoi(argv));
    if (strcmp(azColName, "DAY") == 0) ptr->operator[](arr)->updateDay(atoi(argv));
    if (strcmp(azColName, "YEAR") == 0) ptr->operator[](arr)->updateYear(atoi(argv));
    if (strcmp(azColName, "COMP_TIME") == 0) ptr->operator[](arr)->updateCompTime(atoi(argv));
    if (strcmp(azColName, "SERVICE_NAME") == 0) ptr->operator[](arr)->updateServiceName(argv);
    if (strcmp(azColName, "SERVICE_CODE") == 0) ptr->operator[](arr)->updateServiceNum(atoi(argv));
    if (strcmp(azColName, "FEE") == 0) ptr->operator[](arr)->updateFee(atoi(argv));
    if (strcmp(azColName, "COMMENT") == 0) ptr->operator[](arr)->updateComment(argv);  
}


int Chocoholics::deleteMember(const int key) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);


    string q = "DELETE FROM USERS WHERE ID = ";
    q += to_string(key);
    int exit = sqlite3_exec(DB, q.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : DeleteMember : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}


    string q1 = "DELETE FROM SERVICES WHERE PARENT_ID = ";
    q += to_string(key);
    if (exit != SQLITE_OK) {
		cerr << "Error : DeleteMember : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}

    sqlite3_close(DB);
    return 0;
} 


int Chocoholics::deleteProvider(const int key) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);


    string q = "DELETE FROM USERS WHERE ID = ";
    q += to_string(key);
    int exit = sqlite3_exec(DB, q.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : DeleteMember : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	} 



    string q1 = "DELETE FROM SERVICES WHERE PARENT_ID = ";
    q += to_string(key);
    if (exit != SQLITE_OK) {
		cerr << "Error : DeleteMember : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}

    sqlite3_close(DB);

    return 0;
} 



int Chocoholics::insertService(Service*& ser) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);

    string q = "PRAGMA foreign_keys = ON;";
    int exit = sqlite3_exec(DB, q.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : insertData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	};

    string q1 = "INSERT OR REPLACE INTO DIRECTORY ('SERVICE_NUMBER', 'SERVICE_NAME', 'BILL') VALUES (";
    q1 +="'"; q1 += to_string(ser->getServiceNumber()); q1 +="', ";
    q1 +="'"; q1 += ser->getServiceName(); q1 +="', ";
    q1 +="'"; q1 += to_string(ser->getFee()); q1 +="'); ";

    exit = sqlite3_exec(DB, q1.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : insertData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	};

    sqlite3_close(DB);
    return 0;

}
int Chocoholics::selectService(const int key, Service*& ser) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);

    string query= "SELECT * FROM DIRECTORY WHERE SERVICE_NUMBER = ";
    query += to_string(key);

    ser = new Service;

    int exit = sqlite3_exec(DB, query.c_str(), callbackServices, ser, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : selectData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}

    if (ser->getServiceName().size() == 0) {
        delete ser;
        ser = NULL;
        sqlite3_close(DB);
        return 2;
    }

    sqlite3_close(DB);
    return 0;

}
int Chocoholics::deleteService(const int key) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);

    string q = "DELETE FROM DIRECTORY WHERE SERVICE_NUMBER = ";
    q += to_string(key);
    int exit = sqlite3_exec(DB, q.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : DeleteMember : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	} 

    sqlite3_close(DB);
    return 0;

}
int Chocoholics::selectAllService(vector<Service*>*& ser) {
    char* messageError;
    sqlite3* DB;
    sqlite3_open(path.c_str(), &DB);

    string q= "SELECT * FROM DIRECTORY";

    int exit = sqlite3_exec(DB, q.c_str(), callbackServiceAll, ser, &messageError);
	if (exit != SQLITE_OK) {
		cerr << "Error : selectData : "<<messageError<< endl;
		sqlite3_free(messageError);
        sqlite3_close(DB);
        return 1;
	}

    return 0;
}

int Chocoholics::callbackServices(void* ser, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
		// column name and value
        callbackServiceApp(ser, argv[i], azColName[i]);
	}
	return 0;
}


void Chocoholics::callbackServiceApp(void* ser, char* argv, char* azColName) {
    Service* ptr = reinterpret_cast<Service*> (ser);
    if (strcmp("SERVICE_NUMBER", azColName ) == 0) ptr->updateServiceNum(atoi(argv));
    if (strcmp("SERVICE_NAME", azColName ) == 0) ptr->updateServiceName(argv);
    if (strcmp("BILL", azColName ) == 0) ptr->updateFee(atoi(argv));
}

int Chocoholics::callbackServiceAll(void* ser, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
		// column name and value
        callbackServiceAppAll(ser, argv[i], azColName[i], i);
	}
	return 0;
}

void Chocoholics::callbackServiceAppAll(void* ser, char* argv, char* azColName, int i) {
    vector <Service*>* ptr = reinterpret_cast<vector <Service*>*> (ser);
    if (i % 3 == 0) {
        Service* ser = new Service();
        ptr->push_back(ser);
    }
    
    int arr = ptr->size() - 1;
    if (strcmp("SERVICE_NUMBER", azColName ) == 0) ptr->operator[](arr)->updateServiceNum(atoi(argv));
    if (strcmp("SERVICE_NAME", azColName ) == 0) ptr->operator[](arr)->updateServiceName(argv);
    if (strcmp("BILL", azColName ) == 0) ptr->operator[](arr)->updateFee(atoi(argv));
}

