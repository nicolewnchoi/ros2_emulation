// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ap_interfaces:msg/Score.idl
// generated code does not contain a copyright notice

#ifndef AP_INTERFACES__MSG__DETAIL__SCORE__BUILDER_HPP_
#define AP_INTERFACES__MSG__DETAIL__SCORE__BUILDER_HPP_

#include "ap_interfaces/msg/detail/score__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace ap_interfaces
{

namespace msg
{

namespace builder
{

class Init_Score_game_score
{
public:
  explicit Init_Score_game_score(::ap_interfaces::msg::Score & msg)
  : msg_(msg)
  {}
  ::ap_interfaces::msg::Score game_score(::ap_interfaces::msg::Score::_game_score_type arg)
  {
    msg_.game_score = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ap_interfaces::msg::Score msg_;
};

class Init_Score_player_score
{
public:
  Init_Score_player_score()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Score_game_score player_score(::ap_interfaces::msg::Score::_player_score_type arg)
  {
    msg_.player_score = std::move(arg);
    return Init_Score_game_score(msg_);
  }

private:
  ::ap_interfaces::msg::Score msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ap_interfaces::msg::Score>()
{
  return ap_interfaces::msg::builder::Init_Score_player_score();
}

}  // namespace ap_interfaces

#endif  // AP_INTERFACES__MSG__DETAIL__SCORE__BUILDER_HPP_
