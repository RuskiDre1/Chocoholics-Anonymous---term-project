#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <list>
#include "Information.h"

class Date : public Information {
    public:
        Date();
        Date(const string& user_name, const int id, const int mo, const int day, const int yr);
        Date(const string& user_name, const int id, const Date&);
        Date(const Date&);
        ~Date();

        int getMonth();
        int getDay();
        int getYear();
        time_t getCompTime();

        void updateMonth(const int);
        void updateDay(const int);
        void updateYear(const int);
        void updateCompTime(const int);

    protected:
        int month;
        int day;
        int year;
        time_t comp_time;
};