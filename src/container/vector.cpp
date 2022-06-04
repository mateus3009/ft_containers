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


