#ifndef _TEST_FRAMEWORK_H_
#define _TEST_FRAMEWORK_H_


//#define NewTest(testName, ...) \
//	void test_##testName() { \
//		__VA_ARGS__ \
//	}

#define BeginTestSuite(testSuite) \
    void testSuite_##testSuite(void) {
#define EndTestSuite }

#define NewTest(testName, ...) \
    auto test_##testName = [](void) -> void {\
        __VA_ARGS__ \
    }; \
    test_##testName();

#define ExecuteTestSuite(testSuite) testSuite_##testSuite();

#define DeclareTestSuite(testSuite) extern void testSuite_##testSuite(void);

#endif // _TEST_FRAMEWORK_H_
