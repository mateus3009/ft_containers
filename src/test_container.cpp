#include "test_container.hpp"

#include <bits/stdc++.h>
#include <sys/time.h>

std::map<std::string, test_container::test_function> test_container::tests;

bool test_container::register_test(std::string test, test_function result)
{
    if (tests.find(test) != tests.end())
        return false;
    tests[test] = result;
    return true;
};

void test_container::run()
{
    struct timespec start, end;
    double elapsed;

    for (std::map<std::string, test_container::test_function>::iterator it = tests.begin(); it != tests.end(); ++it)
    {

        clock_gettime(CLOCK_MONOTONIC, &start);
        std::ios_base::sync_with_stdio(false);

        try
        {
            it->second();

            clock_gettime(CLOCK_MONOTONIC, &end);
            elapsed = (end.tv_sec - start.tv_sec) * 1e9;
            elapsed = (elapsed + (end.tv_nsec - start.tv_nsec)) * 1e-9;

            std::cout << GREEN << "OK: " << WHITE << std::fixed << elapsed << std::setprecision(9) << " " << it->first << std::endl;
        }
        catch (const std::exception &e)
        {
            clock_gettime(CLOCK_MONOTONIC, &end);
            elapsed = (end.tv_sec - start.tv_sec) * 1e9;
            elapsed = (elapsed + (end.tv_nsec - start.tv_nsec)) * 1e-9;

            std::cerr << RED << "KO: " << WHITE << std::fixed << elapsed << std::setprecision(9) << " " << it->first << " " << e.what() << std::endl;
        }
    };
};

void test_container::assert_true(bool condition, std::string message)
{
    if (!condition)
        throw std::runtime_error(message.c_str());
};

int main()
{
    test_container::run();
    return 0;
};
