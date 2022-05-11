#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <list>
using namespace std;

void clear();

class Information{
    public:
        Information();
        Information(const string&, const int);
        Information(const Information &to_copy);
        // ~Information();

        string getUserName();
        int getId();

        void updateUserName(const string&);
        void updateId(const int);

        bool operator<(const int);
        bool operator<=(const int);
        bool operator>(const int);
        bool operator>=(const int);
        bool operator!=(const int);
        bool operator==(const int);

    protected:
        string user_name;
        int id;
};