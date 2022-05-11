#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <list>
#include <ctime>
#include "Information.h"
#include "Date.h"
using namespace std;


class Service : public Date{
    public:
        Service();
        Service(const string& user_name, const int id, const int year, const int month, const int date, 
        const string& svcs_name, const int svcs_code, const int cost, const string& comm);
        Service(const Service& to_copy);
        ~Service();

        string getServiceName();
        int getServiceNumber();
        double getFee();
        string getComment();

        void updateServiceName(const string&);
        void updateServiceNum(const int);
        void updateFee(const double);
        void updateComment(const string&);


        bool operator <(const Service&);
        bool operator <=(const Service&);
        bool operator >(const Service&);
        bool operator >=(const Service&);
        bool operator !=(const Service&);
        bool operator ==(const Service&);

        int compare(const Service& cp) const;

    protected:
        string service_name;
        int service_code;
        double fee;
        string comment;
};