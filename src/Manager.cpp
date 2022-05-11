#include "Manager.h"

//manager constructor and destructor
Manager::Manager(){}

Manager::~Manager(){}

//display menu option for user
void Manager::menu(){
    int input;
    clear();

    do
    {
        cout << "------------------------------------------" << endl;
        cout<<"1 = Add member to the ChocAn Database"<<endl;
        cout<<"2 = Add provider to the ChocAn Database"<<endl;
        cout<<"3 = Delete member from the ChocAn Database"<<endl;
        cout <<"4 = Delete provider from the ChocAn Database" << endl;
        cout <<"5 = Update member information" << endl;
        cout <<"6 = Update provider information" << endl;
        cout <<"7 = Generate report about a member" << endl;
        cout <<"8 = Generate report about a provider" << endl;
        cout <<"0 = Exit" << endl;
        cout << "--------------------------------------------" << endl;
        cout<<"Please enter a number corresponding to the task you'd like to execute: ";
        
        cin >> input;
        cin.ignore(100,'\n');
        //checking if input was in range
        if(input < 0 || input > 8)
        {
            cout << "Error input was out of range, please try again." << endl << endl;
            continue;
        }

        //calls appropriate function based on menu choice
        if(input == 1)
            add_member();
        else if(input == 2)
            add_provider();
        else if(input == 3)
            delete_member();
        else if(input == 4)
            delete_provider();
        else if(input == 5)
            update_member();
        else if(input == 6)
            update_provider();
        else if(input == 7)
            generate_member_report();
        else if(input == 8)
            generate_provider_report();
        clear();

    } while (input != 0);
    
    cout << "Have a great day!" << endl;
    return;
}

//generate report about a provider
void Manager::generate_provider_report()
{
    int id_number;
    do
    {
        cout << "What is the ID number of the provider to generate report (9 digits): ";
        cin >> id_number;
        cin.ignore(100,'\n');

        //input was not a number
        if (id_number < 100000000 || id_number > 999999999) 
        {
			cout<<"Error invalid number"<<endl << endl;
            continue;
        }
        else
            break;
    
    } while (true);

    Chocoholics choco;
    Provider * a_pro = NULL;
    choco.selectProvider(id_number,a_pro);

    //provider not in the database
    if(a_pro == NULL)
        cout << "The provider ID does not exist in the ChocAn database." << endl << endl;
    else{
        a_pro->generateReport();
        cout << "The report for the provider has been generated!" << endl << endl;
    }

    return;

}

//generate report about a member
void Manager::generate_member_report()
{
    int id_number;
    do
    {
        cout << "What is the ID number of the member to generate report (9 digits): ";
        cin >> id_number;
        cin.ignore(100,'\n');

        //input was not a number
        if (id_number < 100000000 || id_number > 999999999) 
        {
			cout<<"Error invalid number"<<endl << endl;
            continue;
        }
        else
            break;
    
    } while (true);

    
    Chocoholics choco;
    Member * a_mem = NULL;
    choco.selectMember(id_number,a_mem);

    //member not in the database
    if(a_mem == NULL)
        cout << "The member ID does not exist in the ChocAn database." << endl << endl;
    else{
        a_mem->generateReport();
        cout << "The report for the member sas been generated!" << endl << endl;
    }

    return;

}


//function to delete a provider
void Manager::delete_provider()
{
    int id_number;
    do
    {
        cout << "What is the ID number of the provider to delete (9 digits): ";
        cin >> id_number;
        cin.ignore(100,'\n');

        //input was not a number
        if (id_number < 100000000 || id_number > 999999999) 
        {
			cout<<"Error invalid number"<<endl << endl;
            continue;
        }
        else
            break;
    
    } while (true);

    //delete provider
    Chocoholics choco;
    choco.deleteProvider(id_number);
    cout<<"Provider has been deleted"<<endl;
    return;

}


//function to delete a member
void Manager::delete_member()
{
    int id_number;
    do
    {
        cout << "What is the ID number of the member to delete (9 digits): ";
        cin >> id_number;
        cin.ignore(100,'\n');

        //input was not a number
        if (id_number < 100000000 || id_number > 999999999) 
        {
			cout<<"Error invalid number"<<endl << endl;
            continue;
        }
        else
            break;
    
    } while (true);


    //delete member
    Chocoholics choco;
    choco.deleteMember(id_number);
    cout<<"Member has been deleted"<<endl;

    return;

}

//function to update information about a provider
void Manager::update_provider()
{
    clear();
    int id_number;
    do
    {
        cout << "What is the ID number of the provider to update (9 digits): ";
        cin >> id_number;
        cin.ignore(100,'\n');

        //input was not a number
        if (id_number < 100000000 || id_number > 999999999) 
        {
			cout<<"Error invalid number"<<endl << endl;
            continue;
        }
        else
            break;
    
    } while (true);

    Chocoholics choco;
    Provider* a_pro = NULL;
    choco.selectProvider(id_number,a_pro);

    if(a_pro == NULL){
        cout <<"The provider ID does not exist in the database." << endl << endl;
        return;
    }

    int input;
    cout << '\n';
    cout << "--------------" << endl;
    cout << "1 = Username" << endl;
    cout << "2 = ID number" << endl;
    cout << "3 = Street" << endl;
    cout << "4 = City" << endl;
    cout << "5 = State" << endl;
    cout << "6 = Zip Code" << endl;
    cout << "--------------" << endl;
    cout << "Which information of this provider would you like to update: ";

    //getting user input and checking if valid
    //re-prompt if necessary
    cin >> input;
    cin.ignore(100,'\n');
    while(input < 1 || input > 6)
    {
        cout << "Error invalid input. Please try again." << endl;
        cout << "Enter: ";
        cin >> input;
        cin.ignore(100,'\n');
    }
    //updating the provider information
    if(input == 1)
    {
        string name;
        cout << "Providers's new name: ";
        getline(cin,name,'\n');
        a_pro->updateUserName(name);
    }
    else if(input == 2)
    {
        int id;
        cout << "Provider's new ID number (9 digits): ";
        cin >> id;
        cin.ignore();
        a_pro->updateId(id);
    }
    else if(input == 3)
    {
        string st;
        cout << "Provider's new street address: ";
        getline(cin,st,'\n'); 
        a_pro->updateStreet(st);
    }
    else if(input == 4)
    {
        string city;
        cout << "Provider's new city: ";
        getline(cin,city,'\n');
        a_pro->updateCity(city);
    }
    else if(input == 5)
    {
        string state;
        cout << "Proivder's new state: ";
        getline(cin,state,'\n');
        a_pro->updateState(state);
    }
    else
    {
        int zip;
        cout << "Provider's new zip code: ";
        cin >> zip;
        cin.ignore(100,'\n');
        a_pro->updateZipCode(zip);
    }

    //update provider information in database
    choco.deleteProvider(id_number);
    choco.insertProvider(a_pro);
    cout << "Information updated successfully!" << endl << endl;
    return;
    
}


//function to update information about a member
void Manager::update_member()
{
    clear();
    int id_number;
    do
    {
        cout << "What is the ID number of the member to update (9 digits): ";
        cin >> id_number;
        cin.ignore(100,'\n');

        //input was not a number
        if (id_number < 100000000 || id_number > 999999999) 
        {
			cout<<"Error invalid number"<<endl << endl;
            continue;
        }
        else
            break;
    
    } while (true);

    Chocoholics choco;
    Member* a_mem = NULL;
    choco.selectMember(id_number,a_mem);

    if(a_mem == NULL){
        cout <<"The member ID does not exist in the database." << endl << endl;
        return;
    }

    int input;
    cout << '\n';
    cout << "--------------" << endl;
    cout << "1 = Username" << endl;
    cout << "2 = ID number" << endl;
    cout << "3 = Street" << endl;
    cout << "4 = City" << endl;
    cout << "5 = State" << endl;
    cout << "6 = Zip Code" << endl;
    cout << "--------------" << endl;
    cout << "Which information of this member would you like to update: ";

    //getting user input and checking if valid
    //re-prompt if necessary
    cin >> input;
    cin.ignore(100,'\n');
    while(input < 1 || input > 6)
    {
        cout << "Error invalid input. Please try again." << endl;
        cout << "Enter: ";
        cin >> input;
        cin.ignore(100,'\n');
    }
    //updating the member information
    if(input == 1)
    {
        string name;
        cout << "Member's new name: ";
        getline(cin,name,'\n');
        a_mem->updateUserName(name);
    }
    else if(input == 2)
    {
        int id;
        cout << "Member's new ID number (9 digits): ";
        cin >> id;
        cin.ignore();
        a_mem->updateId(id);
    }
    else if(input == 3)
    {
        string st;
        cout << "Member's new street address: ";
        getline(cin,st,'\n'); 
        a_mem->updateStreet(st);
    }
    else if(input == 4)
    {
        string city;
        cout << "Member's new city: ";
        getline(cin,city,'\n');
        a_mem->updateCity(city);
    }
    else if(input == 5)
    {
        string state;
        cout << "Member's new state: ";
        getline(cin,state,'\n');
        a_mem->updateState(state);
    }
    else
    {
        int zip;
        cout << "Member's new zip code: ";
        cin >> zip;
        cin.ignore(100,'\n');
        a_mem->updateZipCode(zip);
    }

    //update database
    choco.deleteMember(id_number);
    choco.insertMember(a_mem);

    cout << "Information updated successfully!" << endl << endl;
    return;

    
}

//function to add member to the ChocAn Database
void Manager::add_member()
{
    clear();
    string name;
    int id;
    string st;
    string city;
    string state;
    int zip;

    //getting user input regarding a member
    cout << "Member's name: ";
    getline(cin,name,'\n');
    
    cout << "Member's ID number (9 digits): ";
    cin >> id;
    cin.ignore();

    cout << "Member's street address: ";
    getline(cin,st,'\n'); 
    
    cout << "Member's city: ";
    getline(cin,city,'\n');

    cout << "Member's state: ";
    getline(cin,state,'\n');

    cout << "Member's zip code: ";
    cin >> zip;
    cin.ignore(100,'\n');

    //creating member object
    Member * a_mem = new Member(name, id, st, city, state, zip);
    member_list.push_back(a_mem);

    //creating chocholic object for database operation
    Chocoholics choco;
    choco.deleteMember(id);
    choco.insertMember(a_mem);
    
    cout <<"The member has been added to the ChocAn database!" << endl << endl;
    return;
}

//function to add a provider to the ChocAn database
void Manager::add_provider()
{
    clear();
    string name;
    int id;
    string st;
    string city;
    string state;
    int zip;

    //getting user input regarding a member
    cout << "Provider's name: ";
    getline(cin,name,'\n');
    
    cout << "Provider's ID number (9 digits): ";
    cin >> id;
    cin.ignore();

    cout << "Provider's street address: ";
    getline(cin,st,'\n'); 
    
    cout << "Provider's city: ";
    getline(cin,city,'\n');

    cout << "Provider's state: ";
    getline(cin,state,'\n');

    cout << "Provider's zip code: ";
    cin >> zip;
    cin.ignore(100,'\n');

    //creating member object
    Provider * a_pro = new Provider(name, id, st, city, state, zip);
    provider_list.push_back(a_pro); //adding provider in vector

    //creating chocoholic object for databse operation
    Chocoholics choco;
    choco.deleteProvider(id);
    choco.insertProvider(a_pro); //inserting provider into database

    cout <<"The provider has been added to the ChocAn database!" << endl << endl;
    return;
}
