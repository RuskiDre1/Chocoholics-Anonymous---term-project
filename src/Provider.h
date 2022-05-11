#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include "Service.h"
#include "Address.h"
#include "Member.h"
#include "Provider.h"
#include "Chocoholics.h"


using namespace std;

class Provider : public Address{
    public:
        Provider();
        Provider(const string& u_name, const int id, const string& st, const string& city, const string& state, const int zip);
        Provider(Provider&);
        ~Provider();

        bool deleteService(const int);
        void recordService(Service& ser);
        
        int getTotalConsultations();
        int getTotalFee();
    
        bool generateReport();
        int getService(const int id, Service*& ser);

        vector<Service*>& getAllService();

        void menu();


    protected:
        vector<Service*> Service_list;
        int total_consultations;
        int total_fee;

        void printServices();

        void validateService(Member& mem); //prompts the provider for data
        void inputService(Member& mem, Service*& ser_data, int service_code, int service_year, 
        int service_month, int service_day, char* service_comment); //data gets stored


};


class Chocoholics {
    public:
        Chocoholics();

        int insertMember(Member*& mem); //puts data to database
        int insertProvider(Provider*& pro); //puts data to database
        int selectMember(const int key, Member*& mem); //gets data from database
        int selectProvider(const int key, Provider*& pro); //gets data from database

        int deleteMember(const int key);
        int deleteProvider(const int key);


        int insertService(Service*& ser);
        int selectService(const int key, Service*& ser);
        int deleteService(const int key);
        int selectAllService(vector<Service*>*&);

    private:
        static int callbackMem(void* mem, int argc, char** argv, char** azColName);
        static void callbackMemApp(void* mem, char* argv, char* azColName);
        
        static int callbackServiceMem(void* mem, int argc, char** argv, char** azColName);
        static void callbackServiceMemApp(void* ser, char* argv, char* azColName, int i);


        static int callbackPro(void* pro, int argc, char** argv, char** azColName);
        static void callbackProApp(void* pro, char* argv, char* azColName);

        static int callbackServicePro(void* ser, int argc, char** argv, char** azColName);
        static void callbackServiceProApp(void* ser, char* argv, char* azColName, int i);

        static int callbackServices(void* ser, int argc, char** argv, char** azColName);
        static int callbackServiceAll(void* ser, int argc, char** argv, char** azColName);
        static void callbackServiceApp(void* ser, char* argv, char* azColName);
        static void callbackServiceAppAll(void* ser, char* argv, char* azColName, int i);
        


        void createTable();
        string path;
};