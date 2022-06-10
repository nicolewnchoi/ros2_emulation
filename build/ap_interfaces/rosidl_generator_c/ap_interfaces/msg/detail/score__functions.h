// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ap_interfaces:msg\Score.idl
// generated code does not contain a copyright notice

#ifndef AP_INTERFACES__MSG__DETAIL__SCORE__FUNCTIONS_H_
#define AP_INTERFACES__MSG__DETAIL__SCORE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ap_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "ap_interfaces/msg/detail/score__struct.h"

/// Initialize msg/Score message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ap_interfaces__msg__Score
 * )) before or use
 * ap_interfaces__msg__Score__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ap_interfaces
bool
ap_interfaces__msg__Score__init(ap_interfaces__msg__Score * msg);

/// Finalize msg/Score message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ap_interfaces
void
ap_interfaces__msg__Score__fini(ap_interfaces__msg__Score * msg);

/// Create msg/Score message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ap_interfaces__msg__Score__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ap_interfaces
ap_interfaces__msg__Score *
ap_interfaces__msg__Score__create();

/// Destroy msg/Score message.
/**
 * It calls
 * ap_interfaces__msg__Score__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ap_interfaces
void
ap_interfaces__msg__Score__destroy(ap_interfaces__msg__Score * msg);


/// Initialize array of msg/Score messages.
/**
 * It allocates the memory for the number of elements and calls
 * ap_interfaces__msg__Score__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ap_interfaces
bool
ap_interfaces__msg__Score__Sequence__init(ap_interfaces__msg__Score__Sequence * array, size_t size);

/// Finalize array of msg/Score messages.
/**
 * It calls
 * ap_interfaces__msg__Score__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ap_interfaces
void
ap_interfaces__msg__Score__Sequence__fini(ap_interfaces__msg__Score__Sequence * array);

/// Create array of msg/Score messages.
/**
 * It allocates the memory for the array and calls
 * ap_interfaces__msg__Score__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ap_interfaces
ap_interfaces__msg__Score__Sequence *
ap_interfaces__msg__Score__Sequence__create(size_t size);

/// Destroy array of msg/Score messages.
/**
 * It calls
 * ap_interfaces__msg__Score__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ap_interfaces
void
ap_interfaces__msg__Score__Sequence__destroy(ap_interfaces__msg__Score__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // AP_INTERFACES__MSG__DETAIL__SCORE__FUNCTIONS_H_
