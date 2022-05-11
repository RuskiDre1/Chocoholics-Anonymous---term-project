#include "SimpleTestMacro.h"
#include <ctime>
#include "../src/Date.h"

int main() {

	DESCRIBE_TEST(Default Constructor);
	{
		Date d;

		std::time_t t = std::time(NULL);
		std::tm* tm = localtime(&t);
		// fix offsets, see man 3 ctime
		tm->tm_mon += 1;
		tm->tm_year += 1900;

		printf("Today: %d/%d/%d\n", d.getMonth(), d.getDay(), d.getYear());
		ASSERT(d.getMonth() == tm->tm_mon);
		ASSERT(d.getDay() == tm->tm_mday);
		ASSERT(d.getYear() == tm->tm_year);
	}

	return 0;
}
