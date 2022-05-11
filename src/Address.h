#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <list>
#include "Information.h"
using namespace std;

class Address : public Information{ 
    public:
        Address();
        Address(const string& u_name, const int id, const string& st, const string& city, const string& state, const int zip);
        Address(const Information &to_copy);
        // ~Address();

        string getStreet();
        string getCity();
        string getState();
        int getZipCode();

        void updateStreet(const string&);
        void updateCity(const string&);
        void updateState(const string&);
        void updateZipCode(const int);
        
    protected:
        string street;
        string city;
        string state;
        int zip_code;
};

//comment