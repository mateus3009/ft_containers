#include "test_container.hpp"
#include "container/vector.hpp"
#include <vector>

TEST(vector, constructor_default)
{
    NS::vector<int> v;

    ASSERT(v.empty());
    ASSERT(v.size() == 0);
    ASSERT(v.capacity() == 0);
}

TEST(vector, constructor_default_with_allocator)
{
    std::allocator<int> alloc;

    NS::vector<int, std::allocator<int> > v(alloc);

    ASSERT(v.empty());
    ASSERT(v.size() == 0);
    ASSERT(v.capacity() == 0);
}

TEST(vector, constructor_with_size)
{
    NS::vector<int> v(10);

    ASSERT(!v.empty());
    ASSERT(v.size() == 10);
    ASSERT(v.capacity() == 10);
}

TEST(vector, constructor_with_size_and_value)
{
    NS::vector<int> v(10, 42);

    ASSERT(!v.empty());
    ASSERT(v.size() == 10);
    ASSERT(v.capacity() == 10);

    for (int index = 0; index < 10; ++index)
        ASSERT(v[index] == 42);
}

TEST(vector, constructor_with_size_and_value_and_allocator)
{
    std::allocator<int> alloc;

    NS::vector<int> v(10, 42, alloc);

    ASSERT(!v.empty());
    ASSERT(v.size() == 10);
    ASSERT(v.capacity() == 10);

    for (int index = 0; index < 10; ++index)
        ASSERT(v[index] == 42);
}

TEST(vector, max_size)
{
    std::allocator<int> alloc;

    NS::vector<int, std::allocator<int> > v(alloc);

    ASSERT(v.max_size() == alloc.max_size());
}

TEST(vector, size)
{
    NS::vector<int> v;

    ASSERT(v.size() == 0);
}

TEST(vector, size_full)
{
    NS::vector<int> v(10);

    ASSERT(v.size() == 10);
}

TEST(vector, capacity)
{
    NS::vector<int> v;

    ASSERT(v.capacity() == 0);
}

TEST(vector, capacity_full)
{
    NS::vector<int> v(10);

    ASSERT(v.capacity() == 10);
}

TEST(vector, empty)
{
    NS::vector<int> v;

    ASSERT(v.empty());
}

TEST(vector, empty_full)
{
    NS::vector<int> v(10);

    ASSERT(!v.empty());
}

TEST(vector, operator_bracket)
{
    NS::vector<int> v(10, 42);

    for (int index = 0; index < 10; ++index)
        ASSERT(v[index] == 42);
}

TEST(vector, operator_bracket_const)
{
    NS::vector<int> v(10, 42);

    for (int index = 0; index < 10; ++index)
    {
        NS::vector<int>::const_reference c = v[index];
        ASSERT(c == 42);
    }
}

TEST(vector, at)
{
    NS::vector<int> v(10, 42);

    for (int index = 0; index < 10; ++index)
        ASSERT(v.at(index) == 42);
}

TEST(vector, at_const)
{
    NS::vector<int> v(10, 42);

    for (int index = 0; index < 10; ++index)
    {
        NS::vector<int>::const_reference c = v.at(index);
        ASSERT(c == 42);
    }
}

TEST(vector, at_out_of_range)
{
    NS::vector<int> v(10, 42);

    try
    {
        v.at(10);
        ASSERT(false);
    }
    catch(const std::out_of_range& e)
    {
        ASSERT(true)
    }
}

TEST(vector, at_out_of_range_const)
{
    NS::vector<int> v(10, 42);

    try
    {
        NS::vector<int>::const_reference k = v.at(10);
        (void) k;
        ASSERT(false);
    }
    catch(const std::out_of_range& e)
    {
        ASSERT(true)
    }
}


TEST(vector, front)
{
    NS::vector<int> v(10, 42);

    ASSERT(v.front() == 42);
}

TEST(vector, front_const)
{
    NS::vector<int> v(10, 42);

    NS::vector<int>::const_reference c = v.front();

    ASSERT(c == 42);
}


TEST(vector, back)
{
    NS::vector<int> v(10, 42);

    ASSERT(v.back() == 42);
}

TEST(vector, back_const)
{
    NS::vector<int> v(10, 42);

    NS::vector<int>::const_reference c = v.back();

    ASSERT(c == 42);
}

TEST(vector, resize_under_size)
{
    NS::vector<int> v(10, 42);

    v.resize(5);

    ASSERT(v.size() == 5);
    ASSERT(v.capacity() == 10);
}

TEST(vector, resize_under_size_with_value)
{
    NS::vector<int> v(10, 42);

    v.resize(5, 33);

    ASSERT(v.size() == 5);
    ASSERT(v.capacity() == 10);

    for (int index = 0; index < 5; ++index)
        ASSERT(v[index] == 42);
}

TEST(vector, resize_under_capacity)
{
    NS::vector<int> v(20);

    v.resize(10);

    ASSERT(v.size() == 10);
    ASSERT(v.capacity() == 20);
}

TEST(vector, resize_under_capacity_with_value)
{
    NS::vector<int> v(20, 99);

    v.resize(10, 22);

    ASSERT(v.size() == 10);
    ASSERT(v.capacity() == 20);

    for (int index = 0; index < 10; ++index)
        ASSERT(v[index] == 99);
}

TEST(vector, resize_over_capacity)
{
    NS::vector<int> v(10);

    v.resize(20);

    ASSERT(v.size() == 20);
    ASSERT(v.capacity() == 20);
}

TEST(vector, resize_over_capacity_with_value)
{
    NS::vector<int> v(10, 4);

    v.resize(20, 12);

    ASSERT(v.size() == 20);
    ASSERT(v.capacity() == 20);

    for (int index = 0; index < 10; ++index)
        ASSERT(v[index] == 4);

    for (int index = 10; index < 20; ++index)
        ASSERT(v[index] == 12);
}

TEST(vector, get_allocator)
{
    std::allocator<int> alloc;

    NS::vector<int> v(120, 12, alloc);

    ASSERT(v.get_allocator() == alloc);
}

TEST(vector, clear)
{
    NS::vector<int> v(10, 42);

    v.clear();

    ASSERT(v.size() == 0);
    ASSERT(v.capacity() == 10);
}

TEST(vector, clear_empty)
{
    NS::vector<int> v;

    v.clear();

    ASSERT(v.size() == 0);
    ASSERT(v.capacity() == 0);
}

TEST(vector, swap)
{
    NS::vector<int> v1(10, 42);
    NS::vector<int> v2(20, 33);

    v1.swap(v2);

    ASSERT(v1.size() == 20);
    ASSERT(v1.capacity() == 20);
    ASSERT(v1.front() == 33);

    ASSERT(v2.size() == 10);
    ASSERT(v2.capacity() == 10);
    ASSERT(v2.front() == 42);
}

TEST(vector, push_back)
{
    NS::vector<int> v(1, 42);

    v.push_back(33);

    ASSERT(v.size() == 2);
    ASSERT(v.capacity() == 2);
    ASSERT(v.back() == 33);
}

TEST(vector, push_back_resize)
{
    NS::vector<int> v;

    ASSERT(v.size() == 0);
    ASSERT(v.capacity() == 0);

    v.push_back(42);

    ASSERT(v.size() == 1);
    ASSERT(v.capacity() == 1);
    ASSERT(v.back() == 42);

    v.push_back(33);
    ASSERT(v.size() == 2);
    ASSERT(v.capacity() == 2);
    ASSERT(v.back() == 33);

    v.push_back(22);
    ASSERT(v.size() == 3);
    ASSERT(v.capacity() == 4);
    ASSERT(v.back() == 22);
}


