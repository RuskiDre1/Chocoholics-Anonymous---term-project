#include "Member.h"
#include <algorithm>

Member::Member()
{
}

Member::Member(const string &u_name, const int id, const string &st, const string &city, const string &state, const int zip)
    : Address(u_name, id, st, city, state, zip)
{
}

Member::Member(Member &to_copy)
    : Address(to_copy)
{
}

Member::~Member()
{
}

bool Member::operator<(const Member &compare)
{
    return Information::operator<(compare.id);
}
bool Member::operator<=(const Member &compare)
{
    return Information::operator<(compare.id);
}
bool Member::operator>(const Member &compare)
{
    return Information::operator<(compare.id);
}
bool Member::operator>=(const Member &compare)
{
    return Information::operator<(compare.id);
}
bool Member::operator!=(const Member &compare)
{
    return Information::operator<(compare.id);
}
bool Member::operator==(const Member &compare)
{
    return Information::operator<(compare.id);
}

int Member::getService(const int id, Service* ser) {
    for (auto i : consult) {
        if (i->getId() == id) {
            ser = i;
            return 0;
        }
    }
    return 1;
}

void Member::recordService(Service& ser) {
    consult.push_back(&ser);
}

bool Member::generateReport()
{
    //create text file, 
    ofstream myfile;

    time_t now = time(NULL);
    tm *ltm = localtime(&now);

    int temp_year = (1900 + ltm->tm_year);
    int temp_month = (1 + ltm->tm_mon);
    int temp_day = (ltm->tm_mday);

    string filename = getUserName();
    int l = filename.length(); // storing the length of the string
    int c = count(filename.begin(), filename.end(),' '); // counting the number of whitespaces
    remove(filename.begin(), filename.end(),' '); // removing all the whitespaces
    filename.resize(l - c);
    //remove space since file names don't like spaces

    filename += "-";
    filename +=to_string(temp_year);
    filename += "-";
    filename +=to_string(temp_month);
    filename += "-";
    filename +=to_string(temp_day);
    filename +=".txt";

    string file_path = "Reports/";
    file_path +=filename;

    cout<<"Filename: "<<filename<<endl;


    myfile.open (file_path);
    if (!myfile.is_open())
    {
        cout << "Error Generating Member Report" << endl;
        return true;
    }
    //else open
    myfile<<"    Chocoholics Anonymous Member Report    "<<endl;
    myfile<<"\n"<<endl;
    myfile<<getUserName() <<endl;
    myfile<<getStreet()<<endl;
    myfile<<getCity()<<", "<<getState()<<endl;
    myfile<<getZipCode()<<endl;
    myfile<<"Account number: "<<getId()<<endl;
    myfile<<endl;
    myfile<<"        "<<"Service consulted"<<endl;
    cout<<endl;
    for (auto i : consult) {
        //Date of service (MM-DD-YYYY).
        myfile<<"    "<<"Date of Service: "<<i->getMonth()<<"-"<<i->getMonth()<<"-"<<i->getDay()<<endl;
        myfile<<"    "<<"Provider: "<<i->getUserName()<<endl;
        myfile<<"    "<<"Service: "<<i->getServiceName()<<endl;
        myfile<<"\n";
    }
    myfile.close(); 
    return false;
}

vector<Service*>& Member::getAllService() {
    return consult;
}
