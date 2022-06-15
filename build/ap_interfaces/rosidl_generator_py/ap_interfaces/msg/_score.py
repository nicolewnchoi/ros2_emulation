# generated from rosidl_generator_py/resource/_idl.py.em
# with input from ap_interfaces:msg/Score.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'player_score'
# Member 'game_score'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Score(type):
    """Metaclass of message 'Score'."""

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
                'ap_interfaces.msg.Score')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__score
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__score
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__score
            cls._TYPE_SUPPORT = module.type_support_msg__msg__score
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__score

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Score(metaclass=Metaclass_Score):
    """Message class 'Score'."""

    __slots__ = [
        '_player_score',
        '_game_score',
    ]

    _fields_and_field_types = {
        'player_score': 'int16[18]',
        'game_score': 'int16[18]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 18),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 18),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        if 'player_score' not in kwargs:
            self.player_score = numpy.zeros(18, dtype=numpy.int16)
        else:
            self.player_score = numpy.array(kwargs.get('player_score'), dtype=numpy.int16)
            assert self.player_score.shape == (18, )
        if 'game_score' not in kwargs:
            self.game_score = numpy.zeros(18, dtype=numpy.int16)
        else:
            self.game_score = numpy.array(kwargs.get('game_score'), dtype=numpy.int16)
            assert self.game_score.shape == (18, )

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
        if all(self.player_score != other.player_score):
            return False
        if all(self.game_score != other.game_score):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def player_score(self):
        """Message field 'player_score'."""
        return self._player_score

    @player_score.setter
    def player_score(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'player_score' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 18, \
                "The 'player_score' numpy.ndarray() must have a size of 18"
            self._player_score = value
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
                "The 'player_score' field must be a set or sequence with length 18 and each value of type 'int' and each integer in [-32768, 32767]"
        self._player_score = numpy.array(value, dtype=numpy.int16)

    @property
    def game_score(self):
        """Message field 'game_score'."""
        return self._game_score

    @game_score.setter
    def game_score(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'game_score' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 18, \
                "The 'game_score' numpy.ndarray() must have a size of 18"
            self._game_score = value
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
                "The 'game_score' field must be a set or sequence with length 18 and each value of type 'int' and each integer in [-32768, 32767]"
        self._game_score = numpy.array(value, dtype=numpy.int16)
