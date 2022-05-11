#include "Service.h"

Service::Service() {

}

Service::Service(const string& user_name, const int id, const int year, const int month, const int date, 
        const string& svcs_name, const int svcs_code, const int cost, const string& comm) 
        : Date(user_name, id, year, month, date){
            service_name = svcs_name;
            service_code = svcs_code;
            fee = cost;
            comment = comm;

        }
Service::Service(const Service& to_copy)
    :Date(to_copy) {

}

Service::~Service() {

}

string Service::getServiceName() {
    return service_name;

}
int Service::getServiceNumber() {
    return service_code;
}
double Service::getFee() {
    return fee;
}

string Service::getComment() {
    return comment;
}

void Service::updateServiceName(const string& svcs_name) {
    service_name = svcs_name;
}
void Service::updateServiceNum(const int svcs_code) {
    service_code = svcs_code;
}
void Service::updateFee(const double new_fee) {
    fee = new_fee;
}

void Service::updateComment(const string& new_comm) {
    comment = new_comm;
}


bool Service::operator <(const Service& cp) {
    if (year < cp.year) {
        return true;
    } else if (year > cp.year) {
        return false;
    } else if (year == cp.year) {
        if (month < cp.month) {
            return true;
        } else if (month > cp.month) {
            return false;
        } else if (month == cp.month) {
            if (day > cp.day) {
                return true;
            } else if (day > cp.day) {
                return false;
            }
        }
    }
    return false; //means the date is the same
}
bool Service::operator <=(const Service& cp) {
    if (year == cp.year && month == cp.month && day == cp.day) return true;
    else return operator<(cp);
}

bool Service::operator >(const Service& cp) {
    return !(operator<=(cp));
}

bool Service::operator >=(const Service& cp) {
    return !(operator<(cp));
}

bool Service::operator ==(const Service& cp) {
    if (year == cp.year && month == cp.month && day == cp.day) return true;
    else return false;
}
bool Service::operator !=(const Service& cp) {
    return !(operator==(cp));
}

int Service::compare(const Service& cp) const{
    return service_name.compare(cp.service_name);
}