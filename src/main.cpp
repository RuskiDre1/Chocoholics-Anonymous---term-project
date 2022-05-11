#include <iostream>
#include <ctime>
#include <iomanip>
#include "Address.h"
#include "Provider.h"
#include "Manager.h"
using namespace std;

void addData();
void clear() {
	for (int i = 0; i < 75; i++) cout<<"\n";
}


void mainMenu() {
	char input;
	int id;
	Chocoholics choco;

	Provider* provider = NULL;
	Manager* manager;
	// do {
    //     cout << "------------------------------------------" << endl;
	// 	cout<<"1 = Provider"<<endl;
	// 	cout<<"2 = Manager"<<endl;
	// 	cout<<"0 = Exit"<<endl;
    //     cout << "------------------------------------------" << endl;
	// 	cout<<"Enter: ";
	// 	cin>>input;
	// 	cin.ignore(100, '\n');

	// 	if (input == '0') return ;

	// 	cout<<"Please enter your ID Number: ";

	// 	if (!(cin>>id)) {
    //             cout<<"Error not a number, please input a number"<<endl;
	// 			cin.ignore(100, '\n');
    //         } else if (id < 100000000 || id > 999999999) {
	// 			cout<<"Error Invalid Number"<<endl;
	// 			cin.ignore(100, '\n');
	// 		} else {
	// 			cin.ignore(100, '\n');
	// 			if (input == '1') {
	// 				choco.selectProvider(id, provider);
	// 				if (provider != NULL) {
	// 					cout<<"Name: "<<provider->getUserName()<<endl;
	// 					provider->menu();
	// 					choco.deleteProvider(provider->getId());
	// 					choco.insertProvider(provider);
	// 				}
	// 			}

	// 			if (input == '2') {
	// 				manager = new Manager;
	// 				manager -> menu();
	// 				delete manager;
	// 			}
	// 		}
		
	// }while(input != '0');


	do {
		clear();
		cout << "------------------------------------------" << endl;
		cout<<"1 = Provider"<<endl;
		cout<<"2 = Manager"<<endl;
		cout<<"0 = Exit"<<endl;
        cout << "------------------------------------------" << endl;
		cout<<"Enter: ";
		cin>>input;
		cin.ignore(100, '\n');

		if (input == '0') return ;

		if (input == '1') {
			cout<<"Please enter your ID Number: ";
			if (!(cin>>id)) {
                cout<<"Error not a number, please input a number"<<endl;
				cin.ignore(100, '\n');
            } else if (id < 100000000 || id > 999999999) {
				cout<<"Error Invalid Number"<<endl;
				cin.ignore(100, '\n');
			} else {
				cin.ignore(100, '\n');
				choco.selectProvider(id, provider);
				provider->menu();
			}

		} else if (input == '2') {
			manager = new Manager;
			manager -> menu();
			delete manager;
		}

	}while(input != '0');
}


//Members = 100000000, 200000000, 300000000, 400000000 ....
//Providers = 123123123, 234234234, 345345345, 456456456 
//Services = 100000, 200000, 300000, 400000, 500000

int main() {
	// addData(); //only use when the database is empty

	mainMenu();

	return 0;
}




void addData() { //adds data to database for testing
	Chocoholics choco;

	Service* ser1 = new Service;
	Service* ser2 = new Service;
	Service* ser3 = new Service;
	Service* ser4 = new Service;
	Service* ser5 = new Service;
	Service* ser6 = new Service;
	Service* ser7 = new Service;
	Service* ser8 = new Service;
	Service* ser9 = new Service;

	ser1->updateServiceName("Therapy");
	ser1->updateServiceNum(100000);
	ser1->updateFee(299);
	choco.deleteService(100000);
	choco.insertService(ser1);

	ser2->updateServiceName("Chiropractor");
	ser2->updateServiceNum(200000);
	ser2->updateFee(120);
	choco.deleteService(200000);
	choco.insertService(ser2);
	
	ser3->updateServiceName("Counseling");
	ser3->updateServiceNum(300000);
	ser3->updateFee(199);
	choco.deleteService(300000);
	choco.insertService(ser3);

	ser4->updateServiceName("Massage");
	ser4->updateServiceNum(400000);
	ser4->updateFee(70);
	choco.deleteService(400000);
	choco.insertService(ser4);


	ser5->updateServiceName("Dentist");
	ser5->updateServiceNum(500000);
	ser5->updateFee(150);
	choco.deleteService(500000);
	choco.insertService(ser5);

	ser6->updateServiceName("Personal Trainer");
	ser6->updateServiceNum(600000);
	ser6->updateFee(249);
	choco.deleteService(600000);
	choco.insertService(ser6);

	ser7->updateServiceName("Dietitian");
	ser7->updateServiceNum(700000);
	ser7->updateFee(350);
	choco.deleteService(700000);
	choco.insertService(ser7);

	ser8->updateServiceName("Nutrition");
	ser8->updateServiceNum(800000);
	ser8->updateFee(330);
	choco.deleteService(800000);
	choco.insertService(ser8);

	ser9->updateServiceName("Doctor");
	ser9->updateServiceNum(900000);
	ser9->updateFee(999);
	choco.deleteService(900000);
	choco.insertService(ser9);


	Member* m1 = new Member("John Smith", 100000000, "123 NE Glison ST", "Portland", "OR", 97000);
	Member* m2 = new Member("Mohsin Leon", 200000000, "1111 N 456TH St", "Seattle", "WA", 98200);
	Member* m3 = new Member("Simra Preston", 300000000, "5 South Pawnee Court", "Chesapeake", "VA ", 23320);
	Member* m4 = new Member("Black Jesus", 400000000, "00000 SKY", "Heaven", "HV", 0);
	Member* m5 = new Member("Maryam Rasmussen", 500000000, "4 East East Avenue", "Miami", "FL", 33125);

	choco.deleteMember(100000000);
	choco.deleteMember(200000000);
	choco.deleteMember(300000000);
	choco.deleteMember(400000000);
	choco.deleteMember(500000000);


	choco.insertMember(m1);
	choco.insertMember(m2);
	choco.insertMember(m3);
	choco.insertMember(m4);
	choco.insertMember(m5);
	
	

	Provider* p1 = new Provider("Kaiser Permanente", 123123123, "500 NE Multnomah St", "Portland", "OR", 97232);
	Provider* p2 = new Provider("Providence", 234234234, "456 SW Stark St", "Portland", "OR", 97069);
	Provider* p3 = new Provider("KingSong", 345345345, "456 SW Stark St", "Portland", "OR", 97000);
	Provider* p4 = new Provider("Aetna", 456456456, "826 SE Belmont St", "Portland", "OR", 97214);
	

	choco.deleteProvider(123123123);
	choco.deleteProvider(234234234);
	choco.deleteProvider(345345345);
	choco.deleteProvider(456456456);


	choco.insertProvider(p1);
	choco.insertProvider(p2);
	choco.insertProvider(p3);
	choco.insertProvider(p4);

}