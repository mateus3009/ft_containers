#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include <iterator>

namespace ft
{
  // Const-volatile modifications.

  /// remove_const
  template <typename _Tp>
  struct remove_const { typedef _Tp type; };

  template <typename _Tp>
  struct remove_const<_Tp const> { typedef _Tp type; };

  /// remove_volatile
  template <typename _Tp>
  struct remove_volatile { typedef _Tp type; };

  template <typename _Tp>
  struct remove_volatile<_Tp volatile> { typedef _Tp type; };

  /// remove_cv
  template <typename _Tp>
  struct remove_cv
  { typedef typename remove_const<typename remove_volatile<_Tp>::type>::type type; };

  template <typename _Tp, _Tp __v>
  struct integral_constant
  {
    static const _Tp value = __v;
    typedef _Tp value_type;
    typedef integral_constant<_Tp, __v> type;
  };

  template <typename _Tp, _Tp __v>
  const _Tp integral_constant<_Tp, __v>::value;

  // The type used as a compile-time boolean with true value.
  typedef integral_constant<bool, true> true_type;

  // The type used as a compile-time boolean with false value.
  typedef integral_constant<bool, false> false_type;

  template <typename>
  struct __is_integral_helper : public false_type { };

  template <>
  struct __is_integral_helper<bool> : public true_type { };

  template <>
  struct __is_integral_helper<char> : public true_type { };

  template <>
  struct __is_integral_helper<signed char> : public true_type  { };

  template <>
  struct __is_integral_helper<unsigned char> : public true_type { };

  template <>
  struct __is_integral_helper<short> : public true_type { };

  template <>
  struct __is_integral_helper<unsigned short> : public true_type { };

  template <>
  struct __is_integral_helper<int> : public true_type { };

  template <>
  struct __is_integral_helper<unsigned int> : public true_type { };

  template <>
  struct __is_integral_helper<long> : public true_type { };

  template <>
  struct __is_integral_helper<unsigned long> : public true_type { };

  template <>
  struct __is_integral_helper<long long> : public true_type { };

  template <>
  struct __is_integral_helper<unsigned long long> : public true_type { };

  template <typename _Tp>
  struct is_integral :
    public __is_integral_helper<typename remove_cv<_Tp>::type>::type { };

  // Primary template.
  /// Define a member typedef @c type only if a boolean constant is true.
  template<bool, typename _Tp = void>
  struct enable_if { };

  // Partial specialization for true.
  template<typename _Tp>
  struct enable_if<true, _Tp> { typedef _Tp type; };

}

#endif
