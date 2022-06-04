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

        void resize(size_type n, const_reference val = value_type())
        {
            const size_type _size = size();
            if (n <= _size)
            {
                _finish = _start + n;
                return ;
            }

            const size_type _capacity = capacity();
            const size_type required = n - _size;
            if (n < _capacity)
            {
                std::uninitialized_fill_n(_finish, required, val);
                return ;
            }

            const pointer new_start = _alloc.allocate(n);
            pointer new_finish = std::uninitialized_copy(_start, _finish, new_start);
            new_finish = std::uninitialized_fill_n(new_finish, required, val);
            _alloc.deallocate(_start, _capacity);
            _start = new_start;
            _finish = new_finish;
            _end_of_storage = _start + n;
        };

        size_type capacity() const { return _end_of_storage - _start; };

        bool empty() const { return _finish == _start; };

        reference operator[](size_type n) { return _start[n]; };

        const_reference operator[](size_type n) const { return _start[n]; };

        reference at(size_type n)
        {
            if (n >= size())
                throw std::out_of_range("vector::at");
            return _start[n];
        };

        const_reference at(size_type n) const
        {
            if (n >= size())
                throw std::out_of_range("vector::at");
            return _start[n];
        };

        reference front() { return _start[0]; };

        const_reference front() const { return _start[0]; };

        reference back() { return _finish[-1]; };

        const_reference back() const { return _finish[-1]; };

        void swap(ft::vector<value_type> &other)
        {
            std::swap(_start, other._start);
            std::swap(_finish, other._finish);
            std::swap(_end_of_storage, other._end_of_storage);
        };

        void clear() { _finish = _start; };

        allocator_type get_allocator() const { return _alloc; };

    private:

        allocator_type _alloc;

        pointer _start;

        pointer _finish;

        pointer _end_of_storage;
    };

}

#endif
