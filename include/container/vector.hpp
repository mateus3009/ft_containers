#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

#include "util/type_traits.hpp"

#include "iterator/vector_iterator.hpp"

#include "iterator/reverse_iterator.hpp"

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

        typedef typename ft::vector_iterator<value_type> iterator;

        typedef typename ft::vector_iterator<const value_type> const_iterator;

        typedef typename ft::reverse_iterator<iterator> reverse_iterator;

        typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::size_type size_type;

        explicit vector(allocator_type const &alloc = allocator_type()) :
            _alloc(alloc), _start(), _finish(), _end_of_storage() {};

        explicit vector(size_type n, const_reference val = value_type(), allocator_type const &alloc = allocator_type()) : _alloc(alloc)
        {
            _start = _alloc.allocate(n);
            _finish = std::uninitialized_fill_n(_start, n, val);
            _end_of_storage = _finish;
        };

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
               typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL) : _alloc(alloc)
        {
            _start = _alloc.allocate(last - first);
            _finish = std::uninitialized_copy(first, last, _start);
            _end_of_storage = _finish;
        };

        vector(const vector &x) : _alloc(x._alloc)
        {
            _start = _alloc.allocate(x.size());
            _finish = std::uninitialized_copy(x._start, x._finish, _start);
            _end_of_storage = _finish;
        };

        vector &operator=(vector const &other)
        {
            if (this == &other)
                return *this;
            const size_type other_size = other.size();
            const size_type this_capacity = capacity();
            if (other_size > this_capacity)
            {
                pointer new_start = _alloc.allocate(other_size);
                _alloc.deallocate(_start, this_capacity);
                _start = new_start;
                _finish = new_start + other_size;
                _end_of_storage = _finish;
            }
            _finish = std::uninitialized_copy(other.begin(), other.end(), _start);
            return *this;
        };

        iterator begin() { return iterator(_start); };

        iterator end() { return iterator(_finish); };

        const_iterator begin() const { return const_iterator(_start); };

        const_iterator end() const { return const_iterator(_finish); };

        reverse_iterator rbegin() { return reverse_iterator(begin()); };

        reverse_iterator rend() { return reverse_iterator(end()); };

        const_reverse_iterator rbegin() const { return const_reverse_iterator(begin()); };

        const_reverse_iterator rend() const { return const_reverse_iterator(end()); };

        ~vector() { _alloc.deallocate(_start, _end_of_storage - _start); };

        size_type size() const { return _finish - _start; };

        size_type max_size() const { return _alloc.max_size(); };

        void resize(size_type n, const_reference val = value_type())
        {
            const size_type _size = size();
            if (n <= _size)
            {
                _finish = _start + n;
                return;
            }

            const size_type _capacity = capacity();
            const size_type required = n - _size;
            if (n < _capacity)
            {
                std::uninitialized_fill_n(_finish, required, val);
                return;
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

        void reserve(size_type n)
        {
            const size_type _capacity = capacity();
            if (n <= _capacity)
                return;

            const pointer new_start = _alloc.allocate(n);
            const pointer new_finish = std::uninitialized_copy(_start, _finish, new_start);
            _alloc.deallocate(_start, _capacity);
            _start = new_start;
            _finish = new_finish;
            _end_of_storage = new_start + n;
        };

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

        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
        {
            if (first == last)
            {
                clear();
                return;
            }

            const size_type n = last - first;
            if (n <= capacity())
            {
                std::uninitialized_copy(first, last, _start);
                _finish = _start + n;
                return;
            }

            const pointer new_start = _alloc.allocate(n);
            const pointer new_finish = std::uninitialized_copy(first, last, new_start);
            _alloc.deallocate(_start, size());
            _start = new_start;
            _finish = new_finish;
            _end_of_storage = new_finish;
        };

        void assign(size_type n, const value_type &val)
        {
            if (n <= capacity())
            {
                std::uninitialized_fill_n(_start, n, val);
                _finish = _start + n;
                return;
            }

            const pointer new_start = _alloc.allocate(n);
            const pointer new_finish = std::uninitialized_fill_n(new_start, n, val);
            _alloc.deallocate(_start, size());
            _start = new_start;
            _finish = new_finish;
            _end_of_storage = new_finish;
        };

        void push_back(const_reference val)
        {
            const size_type _capacity = capacity();
            if (_capacity == size())
                reserve(_capacity == 0 ? 1 : _capacity * 2);
            *_finish = val;
            ++_finish;
        }

        void pop_back()
        {
            if (empty())
                throw std::out_of_range("ft::vector::pop_back");
            --_finish;
        }

        iterator insert(iterator position, const value_type &val)
        {
            if (position == end())
            {
                push_back(val);
                return end() - 1;
            }

            if (capacity() > size())
            {
                std::uninitialized_copy(position, end(), position + 1);
                *position = val;
                ++_finish;
                return position;
            }

            const difference_type distance = std::distance(begin(), position);
            const std::size_t new_capacity = capacity() == 0 ? 1 : size() * 2;
            const pointer new_start = _alloc.allocate(new_capacity);
            pointer new_finish = std::uninitialized_copy(begin(), position, new_start);
            *(new_finish++) = val;
            new_finish = std::uninitialized_copy(position, end(), new_finish);

            _alloc.deallocate(_start, size());

            _start = new_start;
            _finish = new_finish;
            _end_of_storage = new_start + new_capacity;

            return iterator(new_start + distance);
        };

        void insert(iterator position, size_type n, const value_type &val)
        {
            const size_type _size = size();
            const size_type _capacity = capacity();
            const std::size_t available = _capacity - _size;

            if (n <= available)
            {
                std::uninitialized_copy(position, end(), position + n);
                std::uninitialized_fill_n(position, n, val);
                _finish += n;
                return ;
            }

            const std::size_t new_capacity = _capacity == 0 ? 1 : _capacity * 2;
            const pointer new_start = _alloc.allocate(new_capacity);
            pointer new_finish = std::uninitialized_copy(begin(), position, new_start);
            new_finish = std::uninitialized_fill_n(new_finish, n, val);
            new_finish = std::uninitialized_copy(position, end(), new_finish);

            _alloc.deallocate(_start, _capacity);

            _start = new_start;
            _finish = new_finish;
            _end_of_storage = new_start + new_capacity;
        };

        template <class InputIterator>
        void insert(iterator position, InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = NULL)
        {
            const difference_type distance = std::distance(first, last);
            const difference_type available = capacity() - size();

            if (distance <= available)
            {
                std::uninitialized_copy(position, end(), position + distance);
                std::uninitialized_copy(first, last, position);
                _finish += distance;
                return;
            }

            const std::size_t new_capacity = capacity() == 0 ? 1 : size() * 2;
            const pointer new_start = _alloc.allocate(new_capacity);
            const pointer new_finish = std::uninitialized_copy(begin(), position, new_start);
            new_finish = std::uninitialized_copy(first, last, new_finish);
            new_finish = std::uninitialized_copy(position, end(), new_finish);

            _start = new_start;
            _finish = new_finish;
            _end_of_storage = new_start + new_capacity;

            _alloc.deallocate(_start, size());
        };

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

    template <class T, class Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        for (size_t i = 0; i < lhs.size(); ++i)
            if (lhs[i] != rhs[i])
                return false;
        return true;
    }

    template <class T, class Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T, class Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

}

#endif
