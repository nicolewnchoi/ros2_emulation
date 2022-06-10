// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ap_interfaces:msg\Pos.idl
// generated code does not contain a copyright notice

#ifndef AP_INTERFACES__MSG__DETAIL__POS__STRUCT_H_
#define AP_INTERFACES__MSG__DETAIL__POS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'tag_id'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/Pos in the package ap_interfaces.
typedef struct ap_interfaces__msg__Pos
{
  int8_t total;
  int64_t timestamp;
  int16_t x[18];
  int16_t y[18];
  int8_t player_id[18];
  rosidl_runtime_c__String tag_id[18];
  int8_t size[18];
} ap_interfaces__msg__Pos;

// Struct for a sequence of ap_interfaces__msg__Pos.
typedef struct ap_interfaces__msg__Pos__Sequence
{
  ap_interfaces__msg__Pos * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ap_interfaces__msg__Pos__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AP_INTERFACES__MSG__DETAIL__POS__STRUCT_H_
