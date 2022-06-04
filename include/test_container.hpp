#ifndef TEST_CONTAINER_HPP
#define TEST_CONTAINER_HPP

#include <iostream>
#include <map>

struct test_container
{
    typedef void (*test_function)();

    static std::map<std::string, test_function> tests;
    static bool register_test(std::string test, test_function result);
    static void run();
    static void assert_true(bool condition, std::string message);
};

#define WHITE "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

#define __TO_STR__2(x) #x
#define __TO_STR__(x) __TO_STR__2(x)
#define __LINE_STR__ __TO_STR__(__LINE__)

#define ASSERT(condition) test_container::assert_true(condition, __FILE__ ":" __LINE_STR__ " -> " #condition);

#ifndef NS
#define NS foo
#endif

#define TEST2(a, b, ns)                                                                                                 \
    struct test_##a##_##b##ns                                                                                           \
    {                                                                                                                   \
        static bool isRegistered;                                                                                       \
        static void test();                                                                                             \
    };                                                                                                                  \
    bool test_##a##_##b##ns::isRegistered = test_container::register_test(#a "_" #b "_" #ns, test_##a##_##b##ns::test); \
    void test_##a##_##b##ns::test()

#define TEST3(a, b, ns) TEST2(a, b, ns)

#define TEST(a, b) TEST3(a, b, NS)

#endif
