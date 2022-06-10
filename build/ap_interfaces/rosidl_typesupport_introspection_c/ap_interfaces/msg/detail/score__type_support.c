// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ap_interfaces:msg\Score.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ap_interfaces/msg/detail/score__rosidl_typesupport_introspection_c.h"
#include "ap_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ap_interfaces/msg/detail/score__functions.h"
#include "ap_interfaces/msg/detail/score__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void Score__rosidl_typesupport_introspection_c__Score_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ap_interfaces__msg__Score__init(message_memory);
}

void Score__rosidl_typesupport_introspection_c__Score_fini_function(void * message_memory)
{
  ap_interfaces__msg__Score__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember Score__rosidl_typesupport_introspection_c__Score_message_member_array[2] = {
  {
    "player_score",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    18,  // array size
    false,  // is upper bound
    offsetof(ap_interfaces__msg__Score, player_score),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "game_score",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    18,  // array size
    false,  // is upper bound
    offsetof(ap_interfaces__msg__Score, game_score),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers Score__rosidl_typesupport_introspection_c__Score_message_members = {
  "ap_interfaces__msg",  // message namespace
  "Score",  // message name
  2,  // number of fields
  sizeof(ap_interfaces__msg__Score),
  Score__rosidl_typesupport_introspection_c__Score_message_member_array,  // message members
  Score__rosidl_typesupport_introspection_c__Score_init_function,  // function to initialize message memory (memory has to be allocated)
  Score__rosidl_typesupport_introspection_c__Score_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t Score__rosidl_typesupport_introspection_c__Score_message_type_support_handle = {
  0,
  &Score__rosidl_typesupport_introspection_c__Score_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ap_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ap_interfaces, msg, Score)() {
  if (!Score__rosidl_typesupport_introspection_c__Score_message_type_support_handle.typesupport_identifier) {
    Score__rosidl_typesupport_introspection_c__Score_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &Score__rosidl_typesupport_introspection_c__Score_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
