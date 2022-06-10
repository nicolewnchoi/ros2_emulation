// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ap_interfaces:msg\Score.idl
// generated code does not contain a copyright notice
#include "ap_interfaces/msg/detail/score__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
ap_interfaces__msg__Score__init(ap_interfaces__msg__Score * msg)
{
  if (!msg) {
    return false;
  }
  // player_score
  // game_score
  return true;
}

void
ap_interfaces__msg__Score__fini(ap_interfaces__msg__Score * msg)
{
  if (!msg) {
    return;
  }
  // player_score
  // game_score
}

ap_interfaces__msg__Score *
ap_interfaces__msg__Score__create()
{
  ap_interfaces__msg__Score * msg = (ap_interfaces__msg__Score *)malloc(sizeof(ap_interfaces__msg__Score));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ap_interfaces__msg__Score));
  bool success = ap_interfaces__msg__Score__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ap_interfaces__msg__Score__destroy(ap_interfaces__msg__Score * msg)
{
  if (msg) {
    ap_interfaces__msg__Score__fini(msg);
  }
  free(msg);
}


bool
ap_interfaces__msg__Score__Sequence__init(ap_interfaces__msg__Score__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ap_interfaces__msg__Score * data = NULL;
  if (size) {
    data = (ap_interfaces__msg__Score *)calloc(size, sizeof(ap_interfaces__msg__Score));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ap_interfaces__msg__Score__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ap_interfaces__msg__Score__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
ap_interfaces__msg__Score__Sequence__fini(ap_interfaces__msg__Score__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ap_interfaces__msg__Score__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

ap_interfaces__msg__Score__Sequence *
ap_interfaces__msg__Score__Sequence__create(size_t size)
{
  ap_interfaces__msg__Score__Sequence * array = (ap_interfaces__msg__Score__Sequence *)malloc(sizeof(ap_interfaces__msg__Score__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ap_interfaces__msg__Score__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ap_interfaces__msg__Score__Sequence__destroy(ap_interfaces__msg__Score__Sequence * array)
{
  if (array) {
    ap_interfaces__msg__Score__Sequence__fini(array);
  }
  free(array);
}
