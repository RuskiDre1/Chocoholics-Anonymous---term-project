#include "Provider.h"
#include <algorithm>

Provider::Provider()
{
    total_consultations = 0;
    total_fee = 0;
}

Provider::~Provider() {
    for (auto i : Service_list) {
        delete i;
    }
    Service_list.clear();
}

Provider::Provider(const string &u_name, const int id, const string &st, const string &city, const string &state, const int zip) : Address(u_name, id, st, city, state, zip)
{
    total_consultations = 0;
    total_fee = 0;
}

Provider::Provider(Provider &source) : Address(source)
{

    int size = source.Service_list.size();
    for (int i = 0; i < size; ++i)
    {
        Service_list.push_back(source.Service_list[i]);
    }
    total_consultations = source.total_consultations;
    total_fee = source.total_fee;
}

int Provider::getTotalConsultations()
{
    return total_consultations;
}

int Provider::getTotalFee()
{
    return total_fee;
}

int Provider::getService(const int id, Service*& ser) {
    using namespace std;
    for (auto i : Service_list) {
            cout<<"Service ID: "<<i->getServiceNumber()<<endl;
            cout<<"Look ID: "<<id<<endl;
            if (i->getServiceNumber() == id) {
                ser = i;
                return 0;
            }
        }
    return 1;
}


void Provider::recordService(Service& ser) {
    Service_list.push_back(&ser);
}

vector<Service*>& Provider::getAllService() {
    return Service_list;
}


void Provider::menu() {
    using namespace std;
    clear();
    char input;
    do {
        cout<<"Provider: "<<getUserName()<<endl;
        cout << "------------------------------------------" << endl;
        cout<<"1 = Enter information about service provided to a member"<<endl;
        cout<<"2 = Request Provider dictory"<<endl;
        cout<<"0 = Exit"<<endl;
        cout << "------------------------------------------" << endl;
        cout<<"Please enter a number corresponding to the task you'd like to execute: ";

        cin>>input;
        cin.ignore(100, '\n');

        if (input == '1') {
            int mem_id;
            cout<<"Enter Member ID number: ";

            if (!(cin>>mem_id)) {
                cout<<"Error not a number, please input a number"<<endl;
                continue;
            } 
            Chocoholics choco;
            Member* mem;
            if (choco.selectMember(mem_id, mem) == 0 && mem != NULL) {
                if (mem->getUserName().size() == 0) {
                    cout<<"ID not found"<<endl;
                    continue;
                }
                validateService(*mem);
                choco.deleteMember(mem->getId());
                choco.insertMember(mem);
            }
            else cout<<"ID not found"<<endl;

        }else if (input == '2') {
            clear();
            printServices();
        }
    }while(input != '0');
}

void Provider::printServices() {
    Chocoholics choco;

    vector <Service*> services;
    vector <Service*>* ptr = &services;

    choco.selectAllService(ptr);
    if (ptr == NULL) return;

    cout<<endl;
    for (auto i : services) {
        cout<<"Service Name: "<<i->getServiceName()<<endl;
        cout<<"Service Number: "<<i->getServiceNumber()<<endl;
        cout<<"Fee: "<<i->getFee()<<endl;
        cout<<endl;
    }
}


void Provider::validateService(Member& mem) {
    using namespace std;
    char service_comment[100];
    int service_code;
    int service_year;
    int service_month;
    int service_day;
    int input;
    cout << "------------------------------------------" << endl;
    cout<<"Member Name: "<<mem.getUserName()<<endl;
    cout<<"Please input Service code: ";
        if (!(cin >> service_code)) {
            cin.ignore(100, '\n');
            cout<<"INVALID INPUT: CODE"<<endl;
            return;
        } else {
            cin.ignore(100, '\n');
        }

    Chocoholics choco;
    Service* ser_data;
    //returns only service number, service name, and service fee
    if (choco.selectService(service_code, ser_data) == 0) { 
        cout<<"The service name is: "<<ser_data->getServiceName()<<endl;
        cout<<"Is this correct (y/n): ";
        char flag;
        cin>>flag;
        cin.ignore(100, '\n');

        if (!(flag == 'Y' || flag == 'y')) {
            cout<<"Please try again"<<endl;
            return;
        } 
    }
    clear();
    cout << "------------------------------------------" << endl;
    do {
        input = 1;
        cout<<"Please input Month: ";
        if (!(cin >> input)) {
            cin.ignore(100, '\n');
            cout<<"INVALID INPUT: NOT A NUMBER"<<endl;
        }else if(input <= 0 || input > 12) {
            cin.ignore(100, '\n');
            cout<<"INVALID INPUT: "<<input<<" MONTH NOT POSSIBLE"<<endl;
            input = 1;
        } else {
            cin.ignore(100, '\n');
            service_month = input;
            input = 0;
        }
    }while(input != 0);

    do {
        input = 1;
        cout<<"Please input Day: ";
        if (!(cin >> input)) {
            cin.ignore(100, '\n');
            cout<<"INVALID INPUT: NOT A NUMBER"<<endl;
        }else if(input <= 0 || input > 31) {
            cin.ignore(100, '\n');
            cout<<"INVALID INPUT: "<<input<<" DAY NOT POSSIBLE"<<endl;
            input = 1;
        } else {
            cin.ignore(100, '\n');
            service_day = input;
            input = 0;
        }
    }while(input != 0);

    do {
        input = 1;
        cout<<"Please input Year: ";
        if (!(cin >> input)) {
            cin.ignore(100, '\n');
            cout<<"INVALID INPUT: NOT A NUMBER"<<endl;
        }else if(input <= 0) {
            cin.ignore(100, '\n');
            cout<<"INVALID INPUT: "<<input<<" YEAR NOT POSSIBLE"<<endl;
            input = 1;
        } else {
            cin.ignore(100, '\n');
            service_year = input;
            input = 0;
        }
    }while(input != 0);


    cout<<"Please input a comment: ";
    cin.get(service_comment, 100, '\n');
    cin.ignore(100, '\n');

    inputService(mem,ser_data,service_code,service_year,service_month,service_day,service_comment);


}

void Provider::inputService(Member& mem, Service*& ser_data, int service_code, int service_year, int service_month, int service_day, char* service_comment) {
    Service* member_ser = new Service();
    member_ser->updateUserName(user_name);
    member_ser->updateId(id);
    member_ser->updateYear(service_year);
    member_ser->updateMonth(service_month);
    member_ser->updateDay(service_day);
    member_ser->updateServiceName(ser_data->getServiceName());
    member_ser->updateServiceNum(ser_data->getServiceNumber());
    member_ser->updateFee(ser_data->getFee());
    member_ser->updateComment(service_comment);

    mem.recordService(*member_ser);
    //created and recorded service for member
  

    Service* provider_ser = new Service;
    provider_ser->updateUserName(mem.getUserName());
    provider_ser->updateId(mem.getId());
    provider_ser->updateYear(service_year);
    provider_ser->updateMonth(service_month);
    provider_ser->updateDay(service_day);
    provider_ser->updateServiceName(ser_data->getServiceName());
    provider_ser->updateServiceNum(ser_data->getServiceNumber());
    provider_ser->updateFee(ser_data->getFee());
    provider_ser->updateComment(service_comment);

    Service_list.push_back(provider_ser);
    //clear and recoded service for provider
    for (auto i : Service_list) {
        cout << "------------------------------------------" << endl;
        cout<<"Member name: "<<i->getUserName()<<endl;
        cout<<"Member id: "<<i->getId()<<endl;
        cout<<"Date: "<<i->getMonth()<<"/"<<i->getDay()<<"/"<<i->getYear()<<endl;
        cout<<"Service: "<<i->getServiceName()<<endl;
        cout<<"Service number: "<<i->getServiceNumber()<<endl;
        cout<<"Comment: "<<i->getComment()<<endl;
        cout << "------------------------------------------" << endl;
    }
}

bool Provider::generateReport()
{
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

    ofstream myfile;
    
    myfile.open (file_path.c_str());
    if (!myfile.is_open())
    {
        cout << "Error Generating Provider Report" << endl;
        return true;
    }
    //else open

    //Provider name (25 characters). 
    //Provider number (9 digits). 
    //Provider street address (25 characters). 
    //Provider city (14 characters). 
    //Provider state (2 letters). 
    //Provider zip code (5 digits). 
    //For each service provided, the following details are required: 
    //Date of service (MM-DD-YYYY). 
    //Date and time data were received by the computer (MM-DD-YYYY 

    //Member name (25 characters). 
    //Member number (9 digits). 
    //Service code (6 digits). 
    //Fee to be paid (up to $999.99). 
    //Total number of consultations with members (3 digits). 
    //Total fee for the week (up to $99,999.99). 
    
    // myfile << getUserName() << endl;    //Member name (25 characters). 
    // myfile << getId() << endl;          //Member number (9 digits).
    // myfile << getStreet() << endl;      //Member street address (25 characters)
    // myfile << getCity() << endl;        //Member city (14 characters). 
    // myfile << getState() << endl;       //Member state (2 letters). 
    // myfile << getZipCode() << endl;     //Member zip code (5 digits).
    int total = 0;
    for (auto i : Service_list) {
        total += i->getFee();
    }
    myfile<<"    Chocoholics Anonymous Provider Report    "<<endl;
    myfile<<endl;
    myfile<<getUserName()<<endl;
    myfile<<getStreet()<<endl;
    myfile<<getCity()<<", "<<getState()<<endl;
    myfile<<getZipCode()<<endl;
    myfile<<"ID: "<<getId()<<endl;
    myfile<<"\n"<<endl;

    myfile<<"total number of consultations: "<<Service_list.size()<<endl;
    myfile<<"Total fee: "<<total<<endl;

    myfile<<endl;
    myfile<<"        "<<"Service provided"<<endl;
    struct tm * ct;
    time_t c_time;
    for (auto i : Service_list) {
        c_time = i->getCompTime();
        // time (&c_time);
	    ct = localtime (&c_time);
        myfile<<endl;
        myfile<<"    "<<"Date of Service: "<<i->getMonth()<<"-"<<i->getMonth()<<"-"<<i->getDay()<<endl;
        myfile<<"    "<<"Date and time received by computer: "<<(1+ct->tm_mon)<<"-"<<ct->tm_mday<<"-"<<(1900+ct->tm_year)<<" "<<ct->tm_hour<<":"<<ct->tm_min<<":"<<ct->tm_sec<<endl;
        myfile<<"    "<<"Member name: "<<i->getUserName()<<endl;
        myfile<<"    "<<"Member id: "<<i->getId()<<endl;
        myfile<<"    "<<"Service code: "<<i->getServiceNumber()<<endl;
        myfile<<"    "<<"Fee: "<<i->getFee()<<endl;
    }
	
    myfile.close(); 

    return false;
}
