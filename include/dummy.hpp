#ifndef DUMMY_HPP
# define DUMMY_HPP

namespace ft
{

  template <typename T>
  struct dummy
  {
    static int constructed;

    static int destructed;

    T value;

    dummy() : value() { ++constructed; }

    dummy(T value) : value(value) { ++constructed; }

    ~dummy() { ++destructed; }
  };

  template <typename T>
  int dummy<T>::constructed = 0;

  template <typename T>
  int dummy<T>::destructed = 0;

}

#endif
