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

TEST(vector, constructor_range)
{
    std::vector<int> v(10, 42);
    NS::vector<int> v2(v.begin(), v.end());

    ASSERT(v2.size() == 10)
    ASSERT(v.capacity() == 10)
    for (NS::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
        ASSERT(*it == 42)
}

TEST(vector, constructor_range_alloc)
{
    std::vector<int> v(10, 42);
    std::allocator<int> alloc = std::allocator<int>();
    NS::vector<int> v2(v.begin(), v.end(), alloc);

    ASSERT(v2.size() == 10)
    ASSERT(v.capacity() == 10)
    ASSERT(v.get_allocator() == alloc)
    for (NS::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
        ASSERT(*it == 42)
}

TEST(vector, constructor_copy)
{
    NS::vector<int> v(10, 42);
    NS::vector<int> v2(v);

    ASSERT(v2.size() == 10)
    ASSERT(v.capacity() == 10)
    for (NS::vector<int>::iterator it = v2.begin(); it != v2.end(); ++it)
        ASSERT(*it == 42)
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
    catch (const std::out_of_range &e)
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
        (void)k;
        ASSERT(false);
    }
    catch (const std::out_of_range &e)
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

TEST(vector, pop_back)
{
    NS::vector<int> v(10, 42);

    v.pop_back();

    ASSERT(v.size() == 9);
    ASSERT(v.capacity() == 10);
}

TEST(vector, reserve_under_capacity)
{
    NS::vector<int> v(42);

    v.reserve(10);

    ASSERT(v.size() == 42);
    ASSERT(v.capacity() == 42);
}

TEST(vector, reserve_over_capacity)
{
    NS::vector<int> v(20);

    v.reserve(50);

    ASSERT(v.size() == 20);
    ASSERT(v.capacity() == 50);
}

TEST(vector, operator_equal)
{
    NS::vector<int> v1(10, 24);
    NS::vector<int> v2(10, 32);

    v1 = v2;

    ASSERT(v1.size() == 10);
    ASSERT(v1.capacity() == 10);

    for (int index = 0; index < 10; ++index)
        ASSERT(v1[index] == 32);

    ASSERT(v2.size() == 10);
    ASSERT(v2.capacity() == 10);

    for (int index = 0; index < 10; ++index)
        ASSERT(v2[index] == 32);
}

TEST(vector, operator_equal_different_size_and_capacity)
{
    NS::vector<int> v1(8, 24);
    NS::vector<int> v2(20, 32);

    v1.reserve(50);

    v2.resize(17);

    v1 = v2;
    ASSERT(v1.size() == 17);
    ASSERT(v1.capacity() == 50);

    for (int index = 0; index < 17; ++index)
        ASSERT(v1[index] == 32);

    ASSERT(v2.size() == 17);
    ASSERT(v2.capacity() == 20);

    for (int index = 0; index < 17; ++index)
        ASSERT(v2[index] == 32);
}

TEST(vector, operator_equal_different_size_and_capacity_over)
{
    NS::vector<int> v1(20, 24);
    NS::vector<int> v2(20, 32);

    v2.reserve(50);

    v1.resize(17);

    v1 = v2;
    ASSERT(v1.size() == 20);
    ASSERT(v1.capacity() == 20);

    for (int index = 0; index < 17; ++index)
        ASSERT(v1[index] == 32);

    ASSERT(v2.size() == 20);
    ASSERT(v2.capacity() == 50);

    for (int index = 0; index < 20; ++index)
        ASSERT(v2[index] == 32);
}

TEST(vector, pop_back2)
{
    NS::vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    ASSERT(v.size() == 3)
    ASSERT(v.capacity() == 4)
    ASSERT(v[2] == 3)

    v.pop_back();
    ASSERT(v.size() == 2)
    ASSERT(v.capacity() == 4)
    ASSERT(v[2] == 3)

    v.pop_back();
    v.pop_back();

    ASSERT(v.size() == 0)
    ASSERT(v.capacity() == 4)
    ASSERT(v[0] == 1)
    ASSERT(v[1] == 2)
    ASSERT(v[2] == 3)
}

TEST(vector, clear2)
{
    NS::vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    ASSERT(v.size() == 3)
    ASSERT(v.capacity() == 4)
    ASSERT(v[2] == 3)

    v.clear();

    ASSERT(v.size() == 0)
    ASSERT(v.capacity() == 4)
    ASSERT(v[0] == 1)
    ASSERT(v[1] == 2)
    ASSERT(v[2] == 3)
}

TEST(vector, begin2)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    NS::vector<int>::iterator it = a.begin();

    for (int index = 0; index < 10; ++index)
        ASSERT(*it++ == index)
}

TEST(vector, begin_const)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    const NS::vector<int> b(a);

    NS::vector<int>::const_iterator it = b.begin();

    for (int index = 0; index < 10; ++index)
        ASSERT(*it++ == index)
}

TEST(vector, end)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    const NS::vector<int> b(a);

    NS::vector<int>::const_iterator it = b.end();

    for (int index = 9; index >= 0; --index)
        ASSERT(*--it == index)
}

TEST(vector, end_const)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    NS::vector<int>::iterator it = a.end();

    for (int index = 9; index >= 0; --index)
        ASSERT(*--it == index)
}

TEST(vector, begin)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    NS::vector<int> b;

    for (int index = 9; index >= 0; --index)
        b.push_back(index);
}

TEST(vector, rbegin)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    NS::vector<int>::reverse_iterator it = a.rbegin();

    (void)it;
}

TEST(vector, rbegin_const)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    const NS::vector<int> b(a);

    NS::vector<int>::const_reverse_iterator it = b.rbegin();

    (void)it;
}

TEST(vector, rend)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    NS::vector<int>::reverse_iterator it = a.rend();

    (void)it;
}

TEST(vector, rend_const)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    const NS::vector<int> b(a);

    NS::vector<int>::const_reverse_iterator it = b.rend();

    (void)it;
}

TEST(vector, assign_range)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    NS::vector<int> b;

    b.assign(a.begin(), a.end());

    ASSERT(b.size() == 10)
    ASSERT(b.capacity() == 10)

    for (int index = 0; index < 10; ++index)
        ASSERT(b[index] == index)
}

TEST(vector, assign_range_empty)
{
    NS::vector<int> a;

    NS::vector<int> b;

    b.assign(a.begin(), a.end());

    ASSERT(b.size() == 0)
    ASSERT(b.capacity() == 0)
}

TEST(vector, assign_range_under_capacity)
{
    NS::vector<int> a;

    for (int index = 0; index < 5; ++index)
        a.push_back(index);

    NS::vector<int> b(10, 42);

    b.assign(a.begin(), a.end());

    ASSERT(b.size() == 5)
    ASSERT(b.capacity() == 10)

    for (int index = 0; index < 5; ++index)
        ASSERT(b[index] == index)

    for (int index = 5; index < 10; ++index)
        ASSERT(b[index] == 42)
}

TEST(vector, assign_range_over_capacity)
{
    NS::vector<int> a;

    for (int index = 0; index < 10; ++index)
        a.push_back(index);

    NS::vector<int> b(5, 42);

    b.assign(a.begin(), a.end());

    ASSERT(b.size() == 10)
    ASSERT(b.capacity() == 10)

    for (int index = 0; index < 10; ++index)
        ASSERT(b[index] == index)
}

TEST(vector, assign_fill_zero)
{
    NS::vector<int> a(10, 42);

    a.assign(0, 42);

    ASSERT(a.size() == 0)
    ASSERT(a.capacity() == 10)

    for (int index = 0; index < 10; ++index)
        ASSERT(a[index] == 42)
}

TEST(vector, assign_fill)
{
    NS::vector<int> a(10, 42);

    a.assign(10, 123);

    ASSERT(a.size() == 10)
    ASSERT(a.capacity() == 10)

    for (int index = 0; index < 10; ++index)
        ASSERT(a[index] == 123)
}

TEST(vector, assign_fill_under_capacity)
{
    NS::vector<int> b(10, 42);

    b.assign(5, 123);

    ASSERT(b.size() == 5)
    ASSERT(b.capacity() == 10)

    for (int index = 0; index < 5; ++index)
        ASSERT(b[index] == 123)

    for (int index = 5; index < 10; ++index)
        ASSERT(b[index] == 42)
}

TEST(vector, assign_fill_over_capacity)
{
    NS::vector<int> b(5, 42);

    b.assign(10, 123);

    ASSERT(b.size() == 10)
    ASSERT(b.capacity() == 10)

    for (int index = 0; index < 10; ++index)
        ASSERT(b[index] == 123)
}

TEST(vector, insert_single_element)
{
    NS::vector<int> a(10, 0);

    a.insert(a.begin() + 2, 42);

    ASSERT(a.size() == 11)
    ASSERT(a.capacity() == 20)

    for (int index = 0; index < 11; ++index)
        ASSERT(a[index] == 0 || (index == 2 && a[index] == 42))
}

TEST(vector, insert_single_element_begin)
{
    NS::vector<int> a(10, 0);

    a.insert(a.begin(), 42);

    ASSERT(a.size() == 11)
    ASSERT(a.capacity() == 20)

    ASSERT(a[0] == 42)
    for (int index = 1; index < 11; ++index)
        ASSERT(a[index] == 0)
}

TEST(vector, insert_single_element_end)
{
    NS::vector<int> a(10, 0);

    a.insert(a.end(), 42);

    ASSERT(a.size() == 11)
    ASSERT(a.capacity() == 20)

    ASSERT(a[10] == 42)
    for (int index = 0; index < 9; ++index)
        ASSERT(a[index] == 0)
}

TEST(vector, insert_fill)
{
    std::vector<int> a(10, 0);

    a.insert(a.begin() + 2, 1, 42);

    ASSERT(a.size() == 11)
    ASSERT(a.capacity() == 20)

    for (int index = 0; index < 11; ++index)
        ASSERT(a[index] == 0 || (index == 2 && a[index] == 42))
}

TEST(vector, insert_fill_begin)
{
    NS::vector<int> a(10, 0);

    a.insert(a.begin(), 1, 42);

    ASSERT(a.size() == 11)
    ASSERT(a.capacity() == 20)

    ASSERT(a[0] == 42)
    for (int index = 1; index < 11; ++index)
        ASSERT(a[index] == 0)
}

TEST(vector, insert_fill_end)
{
    NS::vector<int> a(10, 0);

    a.insert(a.end(), 1, 42);

    ASSERT(a.size() == 11)
    ASSERT(a.capacity() == 20)

    ASSERT(a[10] == 42)
    for (int index = 0; index < 9; ++index)
        ASSERT(a[index] == 0)
}

TEST(vector, insert_fill_under_capacity)
{
    int b[] = {9, 9, 4, 4, 4, 4, 4, 9, 9, 9, 9, 9};

    NS::vector<int> a(7, 9);

    a.insert(a.begin() + 2, 5, 4);

    ASSERT(a.size() == 12)
    ASSERT(a.capacity() == 14)

    for (int index = 0; index < 12; ++index)
        ASSERT(a[index] == b[index])
}

TEST(vector, operator_equal_true)
{
    int arr[] = {1, 2, 3, 4, 5};

    std::size_t size = sizeof(arr) / sizeof(int);

    NS::vector<int> a(arr, arr + size);
    NS::vector<int> b(arr, arr + size);

    ASSERT(a == b)
}

TEST(vector, operator_equal_false_size)
{
    int aarr[] = {1, 2, 3};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    NS::vector<int> a(aarr, aarr + asize);
    NS::vector<int> b(barr, barr + bsize);

    ASSERT(!(a == b))
}

TEST(vector, operator_equal_false_value)
{
    int aarr[] = {1, 2, 3, 5, 6};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    NS::vector<int> a(aarr, aarr + asize);
    NS::vector<int> b(barr, barr + bsize);

    ASSERT(!(a == b))
}

TEST(vector, operator_less_false_equal)
{
    int arr[] = {1, 2, 3, 4, 5};

    std::size_t size = sizeof(arr) / sizeof(int);

    NS::vector<int> a(arr, arr + size);
    NS::vector<int> b(arr, arr + size);

    ASSERT(!(a < b))
}

TEST(vector, operator_less_true_value)
{
    int aarr[] = {1, 2, 3, 4, 0};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    NS::vector<int> a(aarr, aarr + asize);
    NS::vector<int> b(barr, barr + bsize);

    ASSERT(a < b)
}

TEST(vector, operator_less_true_size)
{
    int aarr[] = {1, 2, 3};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    NS::vector<int> a(aarr, aarr + asize);
    NS::vector<int> b(barr, barr + bsize);

    ASSERT(a < b)
}

TEST(vector, operator_less_false_value)
{
    int aarr[] = {1, 2, 3, 4, 0};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    NS::vector<int> a(aarr, aarr + asize);
    NS::vector<int> b(barr, barr + bsize);

    ASSERT(!(b < a))
}

TEST(vector, operator_less_false_size)
{
    int aarr[] = {1, 2, 3};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    NS::vector<int> a(aarr, aarr + asize);
    NS::vector<int> b(barr, barr + bsize);

    ASSERT(!(b < a))
}

TEST(vector, non_member_swap)
{
    NS::vector<int> foo(5, 100);
    NS::vector<int> bar(3, 200);

    swap(foo, bar);

    ASSERT(foo.size() == 3)
    for (int index = 0; index < 3; ++index)
        ASSERT(foo[index] == 200)

    ASSERT(bar.size() == 5)
    for (int index = 0; index < 5; ++index)
        ASSERT(bar[index] == 100)
}
