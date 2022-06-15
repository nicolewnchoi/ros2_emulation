// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ap_interfaces:msg/Pos.idl
// generated code does not contain a copyright notice
#include "ap_interfaces/msg/detail/pos__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `tag_id`
#include "rosidl_runtime_c/string_functions.h"

bool
ap_interfaces__msg__Pos__init(ap_interfaces__msg__Pos * msg)
{
  if (!msg) {
    return false;
  }
  // total
  // timestamp
  // x
  // y
  // player_id
  // tag_id
  for (size_t i = 0; i < 18; ++i) {
    if (!rosidl_runtime_c__String__init(&msg->tag_id[i])) {
      ap_interfaces__msg__Pos__fini(msg);
      return false;
    }
  }
  // size
  return true;
}

void
ap_interfaces__msg__Pos__fini(ap_interfaces__msg__Pos * msg)
{
  if (!msg) {
    return;
  }
  // total
  // timestamp
  // x
  // y
  // player_id
  // tag_id
  for (size_t i = 0; i < 18; ++i) {
    rosidl_runtime_c__String__fini(&msg->tag_id[i]);
  }
  // size
}

ap_interfaces__msg__Pos *
ap_interfaces__msg__Pos__create()
{
  ap_interfaces__msg__Pos * msg = (ap_interfaces__msg__Pos *)malloc(sizeof(ap_interfaces__msg__Pos));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ap_interfaces__msg__Pos));
  bool success = ap_interfaces__msg__Pos__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ap_interfaces__msg__Pos__destroy(ap_interfaces__msg__Pos * msg)
{
  if (msg) {
    ap_interfaces__msg__Pos__fini(msg);
  }
  free(msg);
}


bool
ap_interfaces__msg__Pos__Sequence__init(ap_interfaces__msg__Pos__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ap_interfaces__msg__Pos * data = NULL;
  if (size) {
    data = (ap_interfaces__msg__Pos *)calloc(size, sizeof(ap_interfaces__msg__Pos));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ap_interfaces__msg__Pos__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ap_interfaces__msg__Pos__fini(&data[i - 1]);
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
ap_interfaces__msg__Pos__Sequence__fini(ap_interfaces__msg__Pos__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ap_interfaces__msg__Pos__fini(&array->data[i]);
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

ap_interfaces__msg__Pos__Sequence *
ap_interfaces__msg__Pos__Sequence__create(size_t size)
{
  ap_interfaces__msg__Pos__Sequence * array = (ap_interfaces__msg__Pos__Sequence *)malloc(sizeof(ap_interfaces__msg__Pos__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ap_interfaces__msg__Pos__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ap_interfaces__msg__Pos__Sequence__destroy(ap_interfaces__msg__Pos__Sequence * array)
{
  if (array) {
    ap_interfaces__msg__Pos__Sequence__fini(array);
  }
  free(array);
}
