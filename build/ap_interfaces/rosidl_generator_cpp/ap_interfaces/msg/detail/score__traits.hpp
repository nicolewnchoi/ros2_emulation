// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ap_interfaces:msg\Score.idl
// generated code does not contain a copyright notice

#ifndef AP_INTERFACES__MSG__DETAIL__SCORE__TRAITS_HPP_
#define AP_INTERFACES__MSG__DETAIL__SCORE__TRAITS_HPP_

#include "ap_interfaces/msg/detail/score__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ap_interfaces::msg::Score>()
{
  return "ap_interfaces::msg::Score";
}

template<>
inline const char * name<ap_interfaces::msg::Score>()
{
  return "ap_interfaces/msg/Score";
}

template<>
struct has_fixed_size<ap_interfaces::msg::Score>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<ap_interfaces::msg::Score>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<ap_interfaces::msg::Score>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AP_INTERFACES__MSG__DETAIL__SCORE__TRAITS_HPP_
