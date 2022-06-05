#ifndef VECTOR_ITEARTOR_HPP
#define VECTOR_ITEARTOR_HPP

#include "iterator/iterator.hpp"
#include <iterator>

namespace ft
{

  template <class T>
  class vector_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
  {
  public:

    typedef typename std::random_access_iterator_tag iterator_category;

    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;

    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;

    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;

    typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;

    vector_iterator() : _value() {}

    vector_iterator(pointer value) : _value(value) {}

    vector_iterator(const vector_iterator &other) : _value(other._value) {}

    vector_iterator &operator=(const vector_iterator &other)
    {
      _value = other._value;
      return *this;
    }

    ~vector_iterator() {}

    bool operator==(const vector_iterator &other) const
    {
      return _value == other._value;
    }

    bool operator!=(const vector_iterator &other) const
    {
      return _value != other._value;
    }

    reference operator*() const
    {
      return *_value;
    }

    pointer operator->() const
    {
      return _value;
    }

    vector_iterator &operator++()
    {
      ++_value;
      return *this;
    }

    vector_iterator operator++(int)
    {
      vector_iterator tmp(*this);
      ++_value;
      return tmp;
    }

    vector_iterator &operator--()
    {
      --_value;
      return *this;
    }

    vector_iterator operator--(int)
    {
      vector_iterator tmp(*this);
      --_value;
      return tmp;
    }

    vector_iterator operator+(const difference_type &n) const
    {
      return vector_iterator(_value + n);
    }

    vector_iterator operator-(const difference_type &n) const
    {
      return vector_iterator(_value - n);
    }

    difference_type operator-(const vector_iterator &other) const
    {
      return _value - other._value;
    }

    bool operator<(const vector_iterator &other) const
    {
      return _value < other._value;
    }

    bool operator>(const vector_iterator &other) const
    {
      return _value > other._value;
    }

    bool operator<=(const vector_iterator &other) const
    {
      return _value <= other._value;
    }

    bool operator>=(const vector_iterator &other) const
    {
      return _value >= other._value;
    }

    vector_iterator &operator+=(const difference_type &n)
    {
      _value += n;
      return *this;
    }

    vector_iterator &operator-=(const difference_type &n)
    {
      _value -= n;
      return *this;
    }

    reference operator[](const std::size_t &n) const
    {
      return *(_value + n);
    }

  private:
    pointer _value;
  };

}

#endif
