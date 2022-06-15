// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ap_interfaces:msg/Score.idl
// generated code does not contain a copyright notice

#ifndef AP_INTERFACES__MSG__DETAIL__SCORE__STRUCT_HPP_
#define AP_INTERFACES__MSG__DETAIL__SCORE__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ap_interfaces__msg__Score __attribute__((deprecated))
#else
# define DEPRECATED__ap_interfaces__msg__Score __declspec(deprecated)
#endif

namespace ap_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Score_
{
  using Type = Score_<ContainerAllocator>;

  explicit Score_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int16_t, 18>::iterator, int16_t>(this->player_score.begin(), this->player_score.end(), 0);
      std::fill<typename std::array<int16_t, 18>::iterator, int16_t>(this->game_score.begin(), this->game_score.end(), 0);
    }
  }

  explicit Score_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : player_score(_alloc),
    game_score(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      std::fill<typename std::array<int16_t, 18>::iterator, int16_t>(this->player_score.begin(), this->player_score.end(), 0);
      std::fill<typename std::array<int16_t, 18>::iterator, int16_t>(this->game_score.begin(), this->game_score.end(), 0);
    }
  }

  // field types and members
  using _player_score_type =
    std::array<int16_t, 18>;
  _player_score_type player_score;
  using _game_score_type =
    std::array<int16_t, 18>;
  _game_score_type game_score;

  // setters for named parameter idiom
  Type & set__player_score(
    const std::array<int16_t, 18> & _arg)
  {
    this->player_score = _arg;
    return *this;
  }
  Type & set__game_score(
    const std::array<int16_t, 18> & _arg)
  {
    this->game_score = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ap_interfaces::msg::Score_<ContainerAllocator> *;
  using ConstRawPtr =
    const ap_interfaces::msg::Score_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ap_interfaces::msg::Score_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ap_interfaces::msg::Score_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ap_interfaces::msg::Score_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ap_interfaces::msg::Score_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ap_interfaces::msg::Score_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ap_interfaces::msg::Score_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ap_interfaces::msg::Score_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ap_interfaces::msg::Score_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ap_interfaces__msg__Score
    std::shared_ptr<ap_interfaces::msg::Score_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ap_interfaces__msg__Score
    std::shared_ptr<ap_interfaces::msg::Score_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Score_ & other) const
  {
    if (this->player_score != other.player_score) {
      return false;
    }
    if (this->game_score != other.game_score) {
      return false;
    }
    return true;
  }
  bool operator!=(const Score_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Score_

// alias to use template instance with default allocator
using Score =
  ap_interfaces::msg::Score_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ap_interfaces

#endif  // AP_INTERFACES__MSG__DETAIL__SCORE__STRUCT_HPP_
