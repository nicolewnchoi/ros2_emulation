# generated from rosidl_generator_py/resource/_idl.py.em
# with input from ap_interfaces:msg\Pos.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'x'
# Member 'y'
# Member 'player_id'
# Member 'size'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Pos(type):
    """Metaclass of message 'Pos'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('ap_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'ap_interfaces.msg.Pos')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__pos
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__pos
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__pos
            cls._TYPE_SUPPORT = module.type_support_msg__msg__pos
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__pos

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Pos(metaclass=Metaclass_Pos):
    """Message class 'Pos'."""

    __slots__ = [
        '_total',
        '_timestamp',
        '_x',
        '_y',
        '_player_id',
        '_tag_id',
        '_size',
    ]

    _fields_and_field_types = {
        'total': 'int8',
        'timestamp': 'int64',
        'x': 'int16[18]',
        'y': 'int16[18]',
        'player_id': 'int8[18]',
        'tag_id': 'string[18]',
        'size': 'int8[18]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int8'),  # noqa: E501
        rosidl_parser.definition.BasicType('int64'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 18),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 18),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int8'), 18),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.UnboundedString(), 18),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int8'), 18),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.total = kwargs.get('total', int())
        self.timestamp = kwargs.get('timestamp', int())
        if 'x' not in kwargs:
            self.x = numpy.zeros(18, dtype=numpy.int16)
        else:
            self.x = numpy.array(kwargs.get('x'), dtype=numpy.int16)
            assert self.x.shape == (18, )
        if 'y' not in kwargs:
            self.y = numpy.zeros(18, dtype=numpy.int16)
        else:
            self.y = numpy.array(kwargs.get('y'), dtype=numpy.int16)
            assert self.y.shape == (18, )
        if 'player_id' not in kwargs:
            self.player_id = numpy.zeros(18, dtype=numpy.int8)
        else:
            self.player_id = numpy.array(kwargs.get('player_id'), dtype=numpy.int8)
            assert self.player_id.shape == (18, )
        self.tag_id = kwargs.get(
            'tag_id',
            [str() for x in range(18)]
        )
        if 'size' not in kwargs:
            self.size = numpy.zeros(18, dtype=numpy.int8)
        else:
            self.size = numpy.array(kwargs.get('size'), dtype=numpy.int8)
            assert self.size.shape == (18, )

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.total != other.total:
            return False
        if self.timestamp != other.timestamp:
            return False
        if all(self.x != other.x):
            return False
        if all(self.y != other.y):
            return False
        if all(self.player_id != other.player_id):
            return False
        if self.tag_id != other.tag_id:
            return False
        if all(self.size != other.size):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def total(self):
        """Message field 'total'."""
        return self._total

    @total.setter
    def total(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'total' field must be of type 'int'"
            assert value >= -128 and value < 128, \
                "The 'total' field must be an integer in [-128, 127]"
        self._total = value

    @property
    def timestamp(self):
        """Message field 'timestamp'."""
        return self._timestamp

    @timestamp.setter
    def timestamp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timestamp' field must be of type 'int'"
            assert value >= -9223372036854775808 and value < 9223372036854775808, \
                "The 'timestamp' field must be an integer in [-9223372036854775808, 9223372036854775807]"
        self._timestamp = value

    @property
    def x(self):
        """Message field 'x'."""
        return self._x

    @x.setter
    def x(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'x' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 18, \
                "The 'x' numpy.ndarray() must have a size of 18"
            self._x = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 18 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'x' field must be a set or sequence with length 18 and each value of type 'int' and each integer in [-32768, 32767]"
        self._x = numpy.array(value, dtype=numpy.int16)

    @property
    def y(self):
        """Message field 'y'."""
        return self._y

    @y.setter
    def y(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'y' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 18, \
                "The 'y' numpy.ndarray() must have a size of 18"
            self._y = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 18 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'y' field must be a set or sequence with length 18 and each value of type 'int' and each integer in [-32768, 32767]"
        self._y = numpy.array(value, dtype=numpy.int16)

    @property
    def player_id(self):
        """Message field 'player_id'."""
        return self._player_id

    @player_id.setter
    def player_id(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int8, \
                "The 'player_id' numpy.ndarray() must have the dtype of 'numpy.int8'"
            assert value.size == 18, \
                "The 'player_id' numpy.ndarray() must have a size of 18"
            self._player_id = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 18 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -128 and val < 128 for val in value)), \
                "The 'player_id' field must be a set or sequence with length 18 and each value of type 'int' and each integer in [-128, 127]"
        self._player_id = numpy.array(value, dtype=numpy.int8)

    @property
    def tag_id(self):
        """Message field 'tag_id'."""
        return self._tag_id

    @tag_id.setter
    def tag_id(self, value):
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 18 and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'tag_id' field must be a set or sequence with length 18 and each value of type 'str'"
        self._tag_id = value

    @property
    def size(self):
        """Message field 'size'."""
        return self._size

    @size.setter
    def size(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int8, \
                "The 'size' numpy.ndarray() must have the dtype of 'numpy.int8'"
            assert value.size == 18, \
                "The 'size' numpy.ndarray() must have a size of 18"
            self._size = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 18 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= -128 and val < 128 for val in value)), \
                "The 'size' field must be a set or sequence with length 18 and each value of type 'int' and each integer in [-128, 127]"
        self._size = numpy.array(value, dtype=numpy.int8)
