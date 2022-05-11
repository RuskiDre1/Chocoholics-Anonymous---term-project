#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <list>
#include "Provider.h"
#include "Member.h"
#include <vector>
using namespace std;

class Manager {
    public:
        Manager();
        ~Manager();
    
        void menu();
        void add_member();
        void add_provider();
        void update_member();
        void update_provider();
        void delete_member();
        void delete_provider();
        void generate_member_report();
        void generate_provider_report();

    protected:
        vector<Provider*> provider_list;
        vector<Member*> member_list;

};