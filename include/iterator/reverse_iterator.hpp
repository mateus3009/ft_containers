/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msales-a <msales-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:10:21 by msales-a          #+#    #+#             */
/*   Updated: 2022/05/29 15:48:58 by msales-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft
{

  /**
   * @brief reverse_iterator is an iterator adaptor that reverses the direction
   * of a given iterator, which must be at least a LegacyBidirectionalIterator
   * or model bidirectional_iterator (since C++20). In other words, when
   * provided with a bidirectional iterator, ft::reverse_iterator produces a
   * new iterator that moves from the end to the beginning of the sequence
   * defined by the underlying bidirectional iterator.
   *
   * @tparam _Iterator Bidirectional iterator type
   *
   * @see https://en.cppreference.com/w/cpp/iterator/reverse_iterator
   */
  template <class Iter>
  class reverse_iterator
  {
  public:

    typedef Iter iterator_type;

    typedef typename Iter::iterator_category iterator_category;

    typedef typename Iter::value_type value_type;

    typedef typename Iter::difference_type difference_type;

    typedef typename Iter::pointer pointer;

    typedef typename Iter::reference reference;

    reverse_iterator() : _value() {}

    explicit reverse_iterator(iterator_type value) : _value(value) {}

    template <class U>
    reverse_iterator(const reverse_iterator<U> &other) : _value(other._value) {}

    ~reverse_iterator() {}

    template <class U>
    reverse_iterator &operator=(const reverse_iterator<U> &other)
    {
      _value = other._value;
      return *this;
    }

    iterator_type base() const { return _value; }


    reference operator*() const
    {
      iterator_type tmp = _value;
      return *--tmp;
    }

    pointer operator->() const { return &(operator*()); }

    reference operator[](const std::size_t &n) const { return _value[-n - 1]; }

    reverse_iterator &operator++()
    {
      --_value;
      return *this;
    }

    reverse_iterator operator++(int)
    {
      reverse_iterator tmp(*this);
      --_value;
      return tmp;
    }

    reverse_iterator &operator+=(const difference_type &n)
    {
      _value -= n;
      return *this;
    }

    reverse_iterator operator+(const difference_type &n) const { return reverse_iterator(_value - n); }

    reverse_iterator &operator--()
    {
      ++_value;
      return *this;
    }

    reverse_iterator operator--(int)
    {
      reverse_iterator tmp(*this);
      ++_value;
      return tmp;
    }

    reverse_iterator &operator-=(const difference_type &n)
    {
      _value += n;
      return *this;
    }

    reverse_iterator operator-(const difference_type &n) const { return reverse_iterator(_value + n); }

    difference_type operator-(const reverse_iterator &other) const { return _value - other._value; }

  private:

    iterator_type _value;

  };

  template< class Iterator1, class Iterator2 >
  bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
  { return lhs.base() == rhs.base(); };

  template< class Iterator1, class Iterator2 >
  bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
  { return lhs.base() == rhs.base(); };

  template< class Iterator1, class Iterator2 >
  bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
  { return lhs.base() == rhs.base(); };

  template< class Iterator1, class Iterator2 >
  bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
  { return lhs.base() == rhs.base(); };

  template< class Iterator1, class Iterator2 >
  bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
  { return lhs.base() == rhs.base(); };

  template< class Iterator1, class Iterator2 >
  bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
  { return lhs.base() == rhs.base(); };

  template< class Iter >
  ft::reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
  { return reverse_iterator<Iter>(it.base() + n); }

  template< class Iterator >
  typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
  { return lhs.base() - rhs.base(); }

}

#endif
