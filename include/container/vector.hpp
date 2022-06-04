#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft
{

    template <class T, class Allocator = std::allocator<T> >
    class vector
    {
    public:

        typedef T value_type;

        typedef Allocator allocator_type;

        typedef typename allocator_type::reference reference;

        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::pointer pointer;

        typedef typename allocator_type::const_pointer const_pointer;

        typedef void iterator;

        typedef void const_iterator;

        typedef void reverse_iterator;

        typedef void const_reverse_iterator;

        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::size_type size_type;

        explicit vector(allocator_type const& alloc = allocator_type()) :
            _alloc(alloc),
            _start(),
            _finish(),
            _end_of_storage()
        {};

        explicit vector(size_type n, const_reference val = value_type(), allocator_type const& alloc = allocator_type()) : _alloc(alloc)
        {
            _start = _alloc.allocate(n);
            _finish = std::uninitialized_fill_n(_start, n, val);
            _end_of_storage = _finish;
        };

        ~vector() { _alloc.deallocate(_start, _end_of_storage - _start); };

        size_type size() const { return _finish - _start; };

        size_type max_size() const { return _alloc.max_size(); };

        size_type capacity() const { return _end_of_storage - _start; };

        bool empty() const { return _finish == _start; };

        reference operator[](size_type n) { return _start[n]; };

    private:
        allocator_type _alloc;
        pointer _start;
        pointer _finish;
        pointer _end_of_storage;
    };

}

#endif
