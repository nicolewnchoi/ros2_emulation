// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from ap_interfaces:msg\Pos.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "ap_interfaces/msg/detail/pos__struct.h"
#include "ap_interfaces/msg/detail/pos__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool ap_interfaces__msg__pos__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[27];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("ap_interfaces.msg._pos.Pos", full_classname_dest, 26) == 0);
  }
  ap_interfaces__msg__Pos * ros_message = _ros_message;
  {  // total
    PyObject * field = PyObject_GetAttrString(_pymsg, "total");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->total = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // timestamp
    PyObject * field = PyObject_GetAttrString(_pymsg, "timestamp");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->timestamp = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // x
    PyObject * field = PyObject_GetAttrString(_pymsg, "x");
    if (!field) {
      return false;
    }
    // TODO(dirk-thomas) use a better way to check the type before casting
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "numpy.ndarray") == 0);
    PyArrayObject * seq_field = (PyArrayObject *)field;
    Py_INCREF(seq_field);
    assert(PyArray_NDIM(seq_field) == 1);
    assert(PyArray_TYPE(seq_field) == NPY_INT16);
    Py_ssize_t size = 18;
    int16_t * dest = ros_message->x;
    for (Py_ssize_t i = 0; i < size; ++i) {
      int16_t tmp = *(npy_int16 *)PyArray_GETPTR1(seq_field, i);
      memcpy(&dest[i], &tmp, sizeof(int16_t));
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // y
    PyObject * field = PyObject_GetAttrString(_pymsg, "y");
    if (!field) {
      return false;
    }
    // TODO(dirk-thomas) use a better way to check the type before casting
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "numpy.ndarray") == 0);
    PyArrayObject * seq_field = (PyArrayObject *)field;
    Py_INCREF(seq_field);
    assert(PyArray_NDIM(seq_field) == 1);
    assert(PyArray_TYPE(seq_field) == NPY_INT16);
    Py_ssize_t size = 18;
    int16_t * dest = ros_message->y;
    for (Py_ssize_t i = 0; i < size; ++i) {
      int16_t tmp = *(npy_int16 *)PyArray_GETPTR1(seq_field, i);
      memcpy(&dest[i], &tmp, sizeof(int16_t));
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // player_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "player_id");
    if (!field) {
      return false;
    }
    // TODO(dirk-thomas) use a better way to check the type before casting
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "numpy.ndarray") == 0);
    PyArrayObject * seq_field = (PyArrayObject *)field;
    Py_INCREF(seq_field);
    assert(PyArray_NDIM(seq_field) == 1);
    assert(PyArray_TYPE(seq_field) == NPY_INT8);
    Py_ssize_t size = 18;
    int8_t * dest = ros_message->player_id;
    for (Py_ssize_t i = 0; i < size; ++i) {
      int8_t tmp = *(npy_int8 *)PyArray_GETPTR1(seq_field, i);
      memcpy(&dest[i], &tmp, sizeof(int8_t));
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // tag_id
    PyObject * field = PyObject_GetAttrString(_pymsg, "tag_id");
    if (!field) {
      return false;
    }
    PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'tag_id'");
    if (!seq_field) {
      Py_DECREF(field);
      return false;
    }
    Py_ssize_t size = 18;
    rosidl_runtime_c__String * dest = ros_message->tag_id;
    for (Py_ssize_t i = 0; i < size; ++i) {
      PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
      if (!item) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      assert(PyUnicode_Check(item));
      PyObject * encoded_item = PyUnicode_AsUTF8String(item);
      if (!encoded_item) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      rosidl_runtime_c__String__assign(&dest[i], PyBytes_AS_STRING(encoded_item));
      Py_DECREF(encoded_item);
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }
  {  // size
    PyObject * field = PyObject_GetAttrString(_pymsg, "size");
    if (!field) {
      return false;
    }
    // TODO(dirk-thomas) use a better way to check the type before casting
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "numpy.ndarray") == 0);
    PyArrayObject * seq_field = (PyArrayObject *)field;
    Py_INCREF(seq_field);
    assert(PyArray_NDIM(seq_field) == 1);
    assert(PyArray_TYPE(seq_field) == NPY_INT8);
    Py_ssize_t size = 18;
    int8_t * dest = ros_message->size;
    for (Py_ssize_t i = 0; i < size; ++i) {
      int8_t tmp = *(npy_int8 *)PyArray_GETPTR1(seq_field, i);
      memcpy(&dest[i], &tmp, sizeof(int8_t));
    }
    Py_DECREF(seq_field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * ap_interfaces__msg__pos__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Pos */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("ap_interfaces.msg._pos");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Pos");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  ap_interfaces__msg__Pos * ros_message = (ap_interfaces__msg__Pos *)raw_ros_message;
  {  // total
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->total);
    {
      int rc = PyObject_SetAttrString(_pymessage, "total", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // timestamp
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->timestamp);
    {
      int rc = PyObject_SetAttrString(_pymessage, "timestamp", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // x
    PyObject * field = NULL;
    field = PyObject_GetAttrString(_pymessage, "x");
    if (!field) {
      return NULL;
    }
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "numpy.ndarray") == 0);
    PyArrayObject * seq_field = (PyArrayObject *)field;
    assert(PyArray_NDIM(seq_field) == 1);
    assert(PyArray_TYPE(seq_field) == NPY_INT16);
    assert(sizeof(npy_int16) == sizeof(int16_t));
    npy_int16 * dst = (npy_int16 *)PyArray_GETPTR1(seq_field, 0);
    int16_t * src = &(ros_message->x[0]);
    memcpy(dst, src, 18 * sizeof(int16_t));
    Py_DECREF(field);
  }
  {  // y
    PyObject * field = NULL;
    field = PyObject_GetAttrString(_pymessage, "y");
    if (!field) {
      return NULL;
    }
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "numpy.ndarray") == 0);
    PyArrayObject * seq_field = (PyArrayObject *)field;
    assert(PyArray_NDIM(seq_field) == 1);
    assert(PyArray_TYPE(seq_field) == NPY_INT16);
    assert(sizeof(npy_int16) == sizeof(int16_t));
    npy_int16 * dst = (npy_int16 *)PyArray_GETPTR1(seq_field, 0);
    int16_t * src = &(ros_message->y[0]);
    memcpy(dst, src, 18 * sizeof(int16_t));
    Py_DECREF(field);
  }
  {  // player_id
    PyObject * field = NULL;
    field = PyObject_GetAttrString(_pymessage, "player_id");
    if (!field) {
      return NULL;
    }
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "numpy.ndarray") == 0);
    PyArrayObject * seq_field = (PyArrayObject *)field;
    assert(PyArray_NDIM(seq_field) == 1);
    assert(PyArray_TYPE(seq_field) == NPY_INT8);
    assert(sizeof(npy_int8) == sizeof(int8_t));
    npy_int8 * dst = (npy_int8 *)PyArray_GETPTR1(seq_field, 0);
    int8_t * src = &(ros_message->player_id[0]);
    memcpy(dst, src, 18 * sizeof(int8_t));
    Py_DECREF(field);
  }
  {  // tag_id
    PyObject * field = NULL;
    size_t size = 18;
    rosidl_runtime_c__String * src = ros_message->tag_id;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    for (size_t i = 0; i < size; ++i) {
      PyObject * decoded_item = PyUnicode_DecodeUTF8(src[i].data, strlen(src[i].data), "strict");
      if (!decoded_item) {
        return NULL;
      }
      int rc = PyList_SetItem(field, i, decoded_item);
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "tag_id", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // size
    PyObject * field = NULL;
    field = PyObject_GetAttrString(_pymessage, "size");
    if (!field) {
      return NULL;
    }
    assert(field->ob_type != NULL);
    assert(field->ob_type->tp_name != NULL);
    assert(strcmp(field->ob_type->tp_name, "numpy.ndarray") == 0);
    PyArrayObject * seq_field = (PyArrayObject *)field;
    assert(PyArray_NDIM(seq_field) == 1);
    assert(PyArray_TYPE(seq_field) == NPY_INT8);
    assert(sizeof(npy_int8) == sizeof(int8_t));
    npy_int8 * dst = (npy_int8 *)PyArray_GETPTR1(seq_field, 0);
    int8_t * src = &(ros_message->size[0]);
    memcpy(dst, src, 18 * sizeof(int8_t));
    Py_DECREF(field);
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
