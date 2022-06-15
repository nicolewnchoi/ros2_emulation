// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ap_interfaces:msg/Score.idl
// generated code does not contain a copyright notice

#ifndef AP_INTERFACES__MSG__DETAIL__SCORE__STRUCT_H_
#define AP_INTERFACES__MSG__DETAIL__SCORE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Score in the package ap_interfaces.
typedef struct ap_interfaces__msg__Score
{
  int16_t player_score[18];
  int16_t game_score[18];
} ap_interfaces__msg__Score;

// Struct for a sequence of ap_interfaces__msg__Score.
typedef struct ap_interfaces__msg__Score__Sequence
{
  ap_interfaces__msg__Score * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ap_interfaces__msg__Score__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AP_INTERFACES__MSG__DETAIL__SCORE__STRUCT_H_
