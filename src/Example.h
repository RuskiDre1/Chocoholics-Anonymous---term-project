#pragma once
#include <iostream>
#include <string>
#include <iterator>
#include <list>

class Address { 
    private:
        std::string name;
        int id;
        std::string Address;
        std::string state;
    
    public:
        void changeName();
        ~Address();
        //more functions

        bool operator ==(const int num) {
            if (this -> id == num) return true;
            else return false;
        }

};


class Serive : public Address {
    private:
        int id;
        int cost;
};


class Member : public Address{
    private:
        std::list<Serive>::iterator head;
    public:
        
        

};



class Provider : public Address {
    private:
        std::list<Member>::iterator head;
    public:
        void addMember();
        //more funtions

        

};


class Manger {
    private:
        std::list<Provider>::iterator prohead;
        std::list<Provider>::iterator Memhead;
        
};
