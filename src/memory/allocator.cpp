#include "memory/allocator.hpp"
#include "test_container.hpp"
#include "dummy.hpp"

TEST(allocator, allocate_dont_initialize)
{
  ft::dummy<int>::constructed = 0;
  ft::dummy<int>::destructed = 0;

  NS::allocator<ft::dummy<int> > alloc;
  NS::allocator<ft::dummy<int> >::pointer ptr;

  ptr = alloc.allocate(10);

  alloc.deallocate(ptr, 10);

  ft::dummy<int> i_am_the_one(1);

  ASSERT(1 == ft::dummy<int>::constructed)
  ASSERT(0 == ft::dummy<int>::destructed)
}


TEST(allocator, allocate)
{
  NS::allocator<ft::dummy<int> > alloc;
  NS::allocator<ft::dummy<int> >::pointer ptr;

  ptr = alloc.allocate(100);

  for (int index = 0; index < 100; ++index)
    ptr[index] = ft::dummy<int>(index);

  for (int index = 0; index < 100; ++index)
    ASSERT(index == ptr[index].value)

  alloc.deallocate(ptr, 100);
}

