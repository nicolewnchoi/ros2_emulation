// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ap_interfaces:msg/Pos.idl
// generated code does not contain a copyright notice

#ifndef AP_INTERFACES__MSG__DETAIL__POS__STRUCT_HPP_
#define AP_INTERFACES__MSG__DETAIL__POS__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ap_interfaces__msg__Pos __attribute__((deprecated))
#else
# define DEPRECATED__ap_interfaces__msg__Pos __declspec(deprecated)
#endif

namespace ap_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Pos_
{
  using Type = Pos_<ContainerAllocator>;

  explicit Pos_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->total = 0;
      this->timestamp = 0ll;
      std::fill<typename std::array<int16_t, 18>::iterator, int16_t>(this->x.begin(), this->x.end(), 0);
      std::fill<typename std::array<int16_t, 18>::iterator, int16_t>(this->y.begin(), this->y.end(), 0);
      std::fill<typename std::array<int8_t, 18>::iterator, int8_t>(this->player_id.begin(), this->player_id.end(), 0);
      std::fill<typename std::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>, 18>::iterator, std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>>(this->tag_id.begin(), this->tag_id.end(), "");
      std::fill<typename std::array<int8_t, 18>::iterator, int8_t>(this->size.begin(), this->size.end(), 0);
    }
  }

  explicit Pos_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : x(_alloc),
    y(_alloc),
    player_id(_alloc),
    tag_id(_alloc),
    size(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->total = 0;
      this->timestamp = 0ll;
      std::fill<typename std::array<int16_t, 18>::iterator, int16_t>(this->x.begin(), this->x.end(), 0);
      std::fill<typename std::array<int16_t, 18>::iterator, int16_t>(this->y.begin(), this->y.end(), 0);
      std::fill<typename std::array<int8_t, 18>::iterator, int8_t>(this->player_id.begin(), this->player_id.end(), 0);
      std::fill<typename std::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>, 18>::iterator, std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>>(this->tag_id.begin(), this->tag_id.end(), "");
      std::fill<typename std::array<int8_t, 18>::iterator, int8_t>(this->size.begin(), this->size.end(), 0);
    }
  }

  // field types and members
  using _total_type =
    int8_t;
  _total_type total;
  using _timestamp_type =
    int64_t;
  _timestamp_type timestamp;
  using _x_type =
    std::array<int16_t, 18>;
  _x_type x;
  using _y_type =
    std::array<int16_t, 18>;
  _y_type y;
  using _player_id_type =
    std::array<int8_t, 18>;
  _player_id_type player_id;
  using _tag_id_type =
    std::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>, 18>;
  _tag_id_type tag_id;
  using _size_type =
    std::array<int8_t, 18>;
  _size_type size;

  // setters for named parameter idiom
  Type & set__total(
    const int8_t & _arg)
  {
    this->total = _arg;
    return *this;
  }
  Type & set__timestamp(
    const int64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__x(
    const std::array<int16_t, 18> & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const std::array<int16_t, 18> & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__player_id(
    const std::array<int8_t, 18> & _arg)
  {
    this->player_id = _arg;
    return *this;
  }
  Type & set__tag_id(
    const std::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>, 18> & _arg)
  {
    this->tag_id = _arg;
    return *this;
  }
  Type & set__size(
    const std::array<int8_t, 18> & _arg)
  {
    this->size = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ap_interfaces::msg::Pos_<ContainerAllocator> *;
  using ConstRawPtr =
    const ap_interfaces::msg::Pos_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ap_interfaces::msg::Pos_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ap_interfaces::msg::Pos_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ap_interfaces::msg::Pos_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ap_interfaces::msg::Pos_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ap_interfaces::msg::Pos_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ap_interfaces::msg::Pos_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ap_interfaces::msg::Pos_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ap_interfaces::msg::Pos_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ap_interfaces__msg__Pos
    std::shared_ptr<ap_interfaces::msg::Pos_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ap_interfaces__msg__Pos
    std::shared_ptr<ap_interfaces::msg::Pos_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Pos_ & other) const
  {
    if (this->total != other.total) {
      return false;
    }
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->player_id != other.player_id) {
      return false;
    }
    if (this->tag_id != other.tag_id) {
      return false;
    }
    if (this->size != other.size) {
      return false;
    }
    return true;
  }
  bool operator!=(const Pos_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Pos_

// alias to use template instance with default allocator
using Pos =
  ap_interfaces::msg::Pos_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ap_interfaces

#endif  // AP_INTERFACES__MSG__DETAIL__POS__STRUCT_HPP_
