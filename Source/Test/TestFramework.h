////////////////////////////////////////////////////////////////////////////////
// File:
//
// Description:
//
// Methods:
//
// Fields:
//
// Modification History:
//    Date:        Who:            What:
//  07/25/2019  Tyler Gajewski    Initial Creation
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEST_FRAMEWORK_H_
#define _TEST_FRAMEWORK_H_


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

/*
    Example:
    test_application.cpp
    BeginTestSuite(Application_Coverage_Suite)
        NewTest(Application::initialize)
    EndTestSuit

    test_main.cpp
    DeclareTestSuite(Application_Coverage_Suite)

    int main(void)
    {
        ExecuteTestSuite(Application_Coverage_Suite)
    }
*/
#endif // _TEST_FRAMEWORK_H_
