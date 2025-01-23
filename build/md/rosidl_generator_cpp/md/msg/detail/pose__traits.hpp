// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from md:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef MD__MSG__DETAIL__POSE__TRAITS_HPP_
#define MD__MSG__DETAIL__POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "md/msg/detail/pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace md
{

namespace msg
{

inline void to_flow_style_yaml(
  const Pose & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: theta
  {
    out << "theta: ";
    rosidl_generator_traits::value_to_yaml(msg.theta, out);
    out << ", ";
  }

  // member: linear_velocity
  {
    out << "linear_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.linear_velocity, out);
    out << ", ";
  }

  // member: angular_velocity
  {
    out << "angular_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity, out);
    out << ", ";
  }

  // member: us_1
  {
    out << "us_1: ";
    rosidl_generator_traits::value_to_yaml(msg.us_1, out);
    out << ", ";
  }

  // member: us_2
  {
    out << "us_2: ";
    rosidl_generator_traits::value_to_yaml(msg.us_2, out);
    out << ", ";
  }

  // member: us_3
  {
    out << "us_3: ";
    rosidl_generator_traits::value_to_yaml(msg.us_3, out);
    out << ", ";
  }

  // member: us_4
  {
    out << "us_4: ";
    rosidl_generator_traits::value_to_yaml(msg.us_4, out);
    out << ", ";
  }

  // member: platform_state
  {
    out << "platform_state: ";
    rosidl_generator_traits::value_to_yaml(msg.platform_state, out);
    out << ", ";
  }

  // member: left_motor_state
  {
    out << "left_motor_state: ";
    rosidl_generator_traits::value_to_yaml(msg.left_motor_state, out);
    out << ", ";
  }

  // member: right_motor_state
  {
    out << "right_motor_state: ";
    rosidl_generator_traits::value_to_yaml(msg.right_motor_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Pose & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: theta
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "theta: ";
    rosidl_generator_traits::value_to_yaml(msg.theta, out);
    out << "\n";
  }

  // member: linear_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "linear_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.linear_velocity, out);
    out << "\n";
  }

  // member: angular_velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angular_velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.angular_velocity, out);
    out << "\n";
  }

  // member: us_1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "us_1: ";
    rosidl_generator_traits::value_to_yaml(msg.us_1, out);
    out << "\n";
  }

  // member: us_2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "us_2: ";
    rosidl_generator_traits::value_to_yaml(msg.us_2, out);
    out << "\n";
  }

  // member: us_3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "us_3: ";
    rosidl_generator_traits::value_to_yaml(msg.us_3, out);
    out << "\n";
  }

  // member: us_4
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "us_4: ";
    rosidl_generator_traits::value_to_yaml(msg.us_4, out);
    out << "\n";
  }

  // member: platform_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "platform_state: ";
    rosidl_generator_traits::value_to_yaml(msg.platform_state, out);
    out << "\n";
  }

  // member: left_motor_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_motor_state: ";
    rosidl_generator_traits::value_to_yaml(msg.left_motor_state, out);
    out << "\n";
  }

  // member: right_motor_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_motor_state: ";
    rosidl_generator_traits::value_to_yaml(msg.right_motor_state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Pose & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace md

namespace rosidl_generator_traits
{

[[deprecated("use md::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const md::msg::Pose & msg,
  std::ostream & out, size_t indentation = 0)
{
  md::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use md::msg::to_yaml() instead")]]
inline std::string to_yaml(const md::msg::Pose & msg)
{
  return md::msg::to_yaml(msg);
}

template<>
inline const char * data_type<md::msg::Pose>()
{
  return "md::msg::Pose";
}

template<>
inline const char * name<md::msg::Pose>()
{
  return "md/msg/Pose";
}

template<>
struct has_fixed_size<md::msg::Pose>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<md::msg::Pose>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<md::msg::Pose>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MD__MSG__DETAIL__POSE__TRAITS_HPP_
