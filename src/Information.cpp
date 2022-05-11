#include "Information.h"

//constructors
Information::Information()
{
	id = 0;
}


Information::Information(const string& string_copy, const int id_num)
{
	user_name = string_copy;
	id = id_num;
}


Information::Information(const Information &to_copy)
{
	user_name = to_copy.user_name;
	id = to_copy.id;
}


//update username
void Information::updateUserName(const string& to_update)
{
	user_name = to_update;
}

//update id number
void Information::updateId(const int new_id)
{
	id = new_id;
}

//get the id number
int Information::getId()
{
	return id;
}

//get the user name
string Information::getUserName()
{
	return user_name;
}

//operator overloading 
bool Information::operator==(const int compare)
{
	if(id == compare)
		return true;
	else
		return false;
}

bool Information::operator!=(const int compare)
{
	if(id != compare)
		return true;
	else
		return false;
}

bool Information::operator>=(const int compare)
{
	if(id >= compare)
		return true;
	else
		return false;

}

bool Information::operator>(const int compare)
{
	if(id > compare)
		return true;
	else return false;
}

bool Information::operator<=(const int compare)
{
	if(id <= compare)
		return true;
	else
		return false;
}

bool Information::operator<(const int compare)
{
	if(id <= compare)
		return true;
	else
		return false;
}
