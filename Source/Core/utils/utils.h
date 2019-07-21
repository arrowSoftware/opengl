#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdio>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

//#define DEBUG_PRINTF(message) printf("[%s][%s][%d] %s\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, message);
#define DEBUG_PRINTF(message)

#define describe(name, ...) \
	void test_##name() { \
		__VA_ARGS__ \
	}

#endif // _UTILS_H_
