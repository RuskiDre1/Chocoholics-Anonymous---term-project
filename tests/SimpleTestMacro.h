#include <cassert>
#include <cstdio>

#define ASSERT(condition) do { \
if ((condition)) { printf("\033[32mPASS:\t %s\033[0m\n", #condition); } \
else { printf("\033[31mFAIL:\t %s \t\t[%s]+%d\033[0m\n", #condition, __FILE__, __LINE__); assert(!#condition); } \
} while(0)

#define DESCRIBE_TEST(...) do { \
	printf("> Test %s\n", #__VA_ARGS__); \
} while(0)
