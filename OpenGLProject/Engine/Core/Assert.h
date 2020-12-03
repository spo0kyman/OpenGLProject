#pragma once
#include <string>

#ifdef NDEBUG

//release version
#define ASSERT(condition) (void(0))
#define ASSERT_MSG(consition, message) (void(0))

#else

//debug version
#define ASSERT(condition) _assert((condition), #condition, __FILE__, __LINE__, __func__)
#define ASSERT_MSG(condition, message) _assert((condition), #condition, __FILE__, __LINE__, __func__, message)


#endif

void _assert(bool condition,
	const std::string& conditionString,
	const std::string& filename,
	int line,
	const std::string& functionName,
	const std::string& message = "");