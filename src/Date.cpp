#include "Date.h"
#include <ctime>

Date::Date() {
	std::time_t t =  std::time(NULL);
	if (t == -1) {
		// TODO handle error
	}

	std::tm* tm = std::localtime(&t);

	month = tm->tm_mon + 1;
	day = tm->tm_mday;
	year = tm->tm_year + 1900;
	comp_time = t;
}

Date::Date(const string& user_name, const int id, const int mo, const int day, const int yr) :
	Information(user_name, id),
	month(mo),
	day(day),
	year(yr)
{
	//TODO compute comp_time
}

Date::Date(const Date& d) :
	month(d.month),
	day(d.day),
	year(d.year),
	comp_time(d.comp_time)
{}

Date::~Date() {}

int Date::getMonth() { return month; }
int Date::getDay() { return day; }
int Date::getYear() { return year; }

time_t Date::getCompTime() {
	return comp_time;
}

// TODO needs validation
void Date::updateMonth(const int m) {
	month = m;
}
void Date::updateDay(const int d) {
	day = d;
}
void Date::updateYear(const int y) {
	year = y;
}

void Date::updateCompTime(const int c) {
	comp_time = c;
}
