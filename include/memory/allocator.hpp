#ifndef ALLOCATOR_HPP
# define ALLOCATOR_HPP

# include <stdlib.h>
# include <new>
# include <memory>
# include <cstddef>

namespace ft
{

  template <class T>
  struct allocator
  {
    typedef T value_type;

    typedef T *pointer;

    typedef const T *const_pointer;

    typedef T &reference;

    typedef const T &const_reference;

    typedef std::size_t size_type;

    typedef ptrdiff_t difference_type;

    template <class Type>
    struct rebind
    {
      typedef allocator<Type> other;
    };

    allocator() throw() {}

    allocator(const allocator &) throw() {}

    template <class U>
    allocator(const allocator<U> &) throw() {}

    template <class U>
    bool operator==(const allocator<U> &) const throw() { return true; }

    template <class U>
    bool operator!=(const allocator<U> &) const throw() { return false; }

    pointer address(reference value) const { return &value; }

    const_pointer address(const_reference value) const { return &value; }

    allocator<T> &operator=(const allocator<T> &) { return *this; }

    void construct(pointer place, const_reference value) { new (place) T(value); }

    pointer allocate(size_type n, const void* = NULL) const
    {
      if (n == 0)
        return NULL;

      size_t max_size = static_cast<size_t>(-1) / sizeof(T);
      if (n > max_size)
        throw std::bad_alloc();

      void *const ptr = malloc(n * sizeof(T));
      if (!ptr)
        throw std::bad_alloc();

      return static_cast<pointer>(ptr);
    }

    void deallocate(const_pointer ptr, size_type) const throw()
    {
      free((void *)ptr);
    }

    void destroy(pointer ptr) const
    {
      ptr->~T();
    }

    size_type max_size() const throw()
    {
      return static_cast<size_type>(-1) / sizeof(T);
    }
  };

}

#endif
