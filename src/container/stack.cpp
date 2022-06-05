#include "test_container.hpp"
#include <stack>
#include "container/stack.hpp"
#include <vector>

TEST(stack, constructor_empty)
{
    NS::stack<int> stack;

    ASSERT(stack.empty())
}

TEST(stack, constructor_ft_vector)
{
    ft::vector<int> ctnr(5, 10);
    NS::stack<int, ft::vector<int> > s(ctnr);

    ASSERT(!s.empty())

    s.pop();

    ASSERT(s.size() == 4)
    ASSERT(s.top() == 10)
}

TEST(stack, constructor_std_vector)
{
    std::vector<int> ctnr(5, 10);
    NS::stack<int, std::vector<int> > s(ctnr);

    ASSERT(!s.empty())

    s.pop();

    ASSERT(s.size() == 4)
    ASSERT(s.top() == 10)
}

TEST(stack, push)
{
    NS::stack<int> s;

    s.push(10);

    ASSERT(!s.empty())
    ASSERT(s.size() == 1)
    ASSERT(s.top() == 10)

    s.push(20);

    ASSERT(!s.empty())
    ASSERT(s.size() == 2)
    ASSERT(s.top() == 20)
}

TEST(stack, top)
{
    NS::stack<int> s;

    int index;

    for (index = 0; index < 10; ++index)
        s.push(index);

    --index;

    while (index > 1)
    {
        ASSERT(s.top() == index)
        s.pop();
        --index;
    }
}

TEST(stack, top_const)
{
    const std::vector<int> x(2, 10);

    const NS::stack<int, std::vector<int> > s(x);

    const int k = s.top();

    ASSERT(k == 10)
}

TEST(stack, pop)
{
    NS::stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    ASSERT(!s.empty())
    ASSERT(s.size() == 3)
    ASSERT(s.top() == 30)

    s.pop();
    s.pop();

    ASSERT(s.top() = 10)

    s.pop();

    ASSERT(s.empty())
}

TEST(stack, pop_deque)
{
    NS::stack<int, std::deque<int> > s;

    s.push(10);
    s.push(20);
    s.push(30);

    ASSERT(!s.empty())
    ASSERT(s.size() == 3)
    ASSERT(s.top() == 30)

    s.pop();
    s.pop();

    ASSERT(s.top() = 10)

    s.pop();

    ASSERT(s.empty())
}

TEST(stack, operator_equal_true)
{
    int arr[] = {1, 2, 3, 4, 5};

    std::size_t size = sizeof(arr) / sizeof(int);

    std::vector<int> va(arr, arr + size);
    std::vector<int> vb(arr, arr + size);

    NS::stack<int, std::vector<int> > a(va);
    NS::stack<int, std::vector<int> > b(vb);

    ASSERT(a == b)
}

TEST(stack, operator_equal_false_size)
{
    int aarr[] = {1, 2, 3};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    std::vector<int> va(aarr, aarr + asize);
    std::vector<int> vb(barr, barr + bsize);

    NS::stack<int, std::vector<int> > a(va);
    NS::stack<int, std::vector<int> > b(vb);

    ASSERT(!(a == b))
}

TEST(stack, operator_equal_false_value)
{
    int aarr[] = {1, 2, 3, 5, 6};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    std::vector<int> va(aarr, aarr + asize);
    std::vector<int> vb(barr, barr + bsize);

    NS::stack<int, std::vector<int> > a(va);
    NS::stack<int, std::vector<int> > b(vb);

    ASSERT(!(a == b))
}

TEST(stack, operator_less_false_equal)
{
    int arr[] = {1, 2, 3, 4, 5};

    std::size_t size = sizeof(arr) / sizeof(int);

    std::vector<int> va(arr, arr + size);
    std::vector<int> vb(arr, arr + size);

    NS::stack<int, std::vector<int> > a(va);
    NS::stack<int, std::vector<int> > b(vb);

    ASSERT(!(a < b))
}

TEST(stack, operator_less_true_value)
{
    int aarr[] = {1, 2, 3, 4, 0};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    std::vector<int> va(aarr, aarr + asize);
    std::vector<int> vb(barr, barr + bsize);

    NS::stack<int, std::vector<int> > a(va);
    NS::stack<int, std::vector<int> > b(vb);

    ASSERT(a < b)
}

TEST(stack, operator_less_true_size)
{
    int aarr[] = {1, 2, 3};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    std::vector<int> va(aarr, aarr + asize);
    std::vector<int> vb(barr, barr + bsize);

    NS::stack<int, std::vector<int> > a(va);
    NS::stack<int, std::vector<int> > b(vb);

    ASSERT(a < b)
}

TEST(stack, operator_less_false_value)
{
    int aarr[] = {1, 2, 3, 4, 0};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    std::vector<int> va(aarr, aarr + asize);
    std::vector<int> vb(barr, barr + bsize);

    NS::stack<int, std::vector<int> > a(va);
    NS::stack<int, std::vector<int> > b(vb);

    ASSERT(!(b < a))
}

TEST(stack, operator_less_false_size)
{
    int aarr[] = {1, 2, 3};
    int barr[] = {1, 2, 3, 4, 5};

    std::size_t asize = sizeof(aarr) / sizeof(int);
    std::size_t bsize = sizeof(barr) / sizeof(int);

    std::vector<int> va(aarr, aarr + asize);
    std::vector<int> vb(barr, barr + bsize);

    NS::stack<int, std::vector<int> > a(va);
    NS::stack<int, std::vector<int> > b(vb);

    ASSERT(!(b < a))
}
