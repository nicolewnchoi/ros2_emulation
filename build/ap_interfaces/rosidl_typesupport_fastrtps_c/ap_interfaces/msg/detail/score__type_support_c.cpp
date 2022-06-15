// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from ap_interfaces:msg/Score.idl
// generated code does not contain a copyright notice
#include "ap_interfaces/msg/detail/score__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "ap_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "ap_interfaces/msg/detail/score__struct.h"
#include "ap_interfaces/msg/detail/score__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _Score__ros_msg_type = ap_interfaces__msg__Score;

static bool _Score__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Score__ros_msg_type * ros_message = static_cast<const _Score__ros_msg_type *>(untyped_ros_message);
  // Field name: player_score
  {
    size_t size = 18;
    auto array_ptr = ros_message->player_score;
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: game_score
  {
    size_t size = 18;
    auto array_ptr = ros_message->game_score;
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _Score__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Score__ros_msg_type * ros_message = static_cast<_Score__ros_msg_type *>(untyped_ros_message);
  // Field name: player_score
  {
    size_t size = 18;
    auto array_ptr = ros_message->player_score;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: game_score
  {
    size_t size = 18;
    auto array_ptr = ros_message->game_score;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ap_interfaces
size_t get_serialized_size_ap_interfaces__msg__Score(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Score__ros_msg_type * ros_message = static_cast<const _Score__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name player_score
  {
    size_t array_size = 18;
    auto array_ptr = ros_message->player_score;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name game_score
  {
    size_t array_size = 18;
    auto array_ptr = ros_message->game_score;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Score__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_ap_interfaces__msg__Score(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_ap_interfaces
size_t max_serialized_size_ap_interfaces__msg__Score(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: player_score
  {
    size_t array_size = 18;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: game_score
  {
    size_t array_size = 18;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  return current_alignment - initial_alignment;
}

static size_t _Score__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_ap_interfaces__msg__Score(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_Score = {
  "ap_interfaces::msg",
  "Score",
  _Score__cdr_serialize,
  _Score__cdr_deserialize,
  _Score__get_serialized_size,
  _Score__max_serialized_size
};

static rosidl_message_type_support_t _Score__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Score,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, ap_interfaces, msg, Score)() {
  return &_Score__type_support;
}

#if defined(__cplusplus)
}
#endif
