// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from ap_interfaces:msg\Score.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "ap_interfaces/msg/detail/score__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace ap_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void Score_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) ap_interfaces::msg::Score(_init);
}

void Score_fini_function(void * message_memory)
{
  auto typed_message = static_cast<ap_interfaces::msg::Score *>(message_memory);
  typed_message->~Score();
}

size_t size_function__Score__player_score(const void * untyped_member)
{
  (void)untyped_member;
  return 18;
}

const void * get_const_function__Score__player_score(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 18> *>(untyped_member);
  return &member[index];
}

void * get_function__Score__player_score(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 18> *>(untyped_member);
  return &member[index];
}

size_t size_function__Score__game_score(const void * untyped_member)
{
  (void)untyped_member;
  return 18;
}

const void * get_const_function__Score__game_score(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::array<int16_t, 18> *>(untyped_member);
  return &member[index];
}

void * get_function__Score__game_score(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::array<int16_t, 18> *>(untyped_member);
  return &member[index];
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Score_message_member_array[2] = {
  {
    "player_score",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    18,  // array size
    false,  // is upper bound
    offsetof(ap_interfaces::msg::Score, player_score),  // bytes offset in struct
    nullptr,  // default value
    size_function__Score__player_score,  // size() function pointer
    get_const_function__Score__player_score,  // get_const(index) function pointer
    get_function__Score__player_score,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "game_score",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    18,  // array size
    false,  // is upper bound
    offsetof(ap_interfaces::msg::Score, game_score),  // bytes offset in struct
    nullptr,  // default value
    size_function__Score__game_score,  // size() function pointer
    get_const_function__Score__game_score,  // get_const(index) function pointer
    get_function__Score__game_score,  // get(index) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Score_message_members = {
  "ap_interfaces::msg",  // message namespace
  "Score",  // message name
  2,  // number of fields
  sizeof(ap_interfaces::msg::Score),
  Score_message_member_array,  // message members
  Score_init_function,  // function to initialize message memory (memory has to be allocated)
  Score_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Score_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Score_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace ap_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<ap_interfaces::msg::Score>()
{
  return &::ap_interfaces::msg::rosidl_typesupport_introspection_cpp::Score_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, ap_interfaces, msg, Score)() {
  return &::ap_interfaces::msg::rosidl_typesupport_introspection_cpp::Score_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
