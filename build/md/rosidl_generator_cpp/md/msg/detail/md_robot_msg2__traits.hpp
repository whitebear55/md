// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from md:msg/MdRobotMsg2.idl
// generated code does not contain a copyright notice

#ifndef MD__MSG__DETAIL__MD_ROBOT_MSG2__TRAITS_HPP_
#define MD__MSG__DETAIL__MD_ROBOT_MSG2__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "md/msg/detail/md_robot_msg2__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace md
{

namespace msg
{

inline void to_flow_style_yaml(
  const MdRobotMsg2 & msg,
  std::ostream & out)
{
  out << "{";
  // member: interval_time
  {
    out << "interval_time: ";
    rosidl_generator_traits::value_to_yaml(msg.interval_time, out);
    out << ", ";
  }

  // member: x_pos
  {
    out << "x_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.x_pos, out);
    out << ", ";
  }

  // member: y_pos
  {
    out << "y_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.y_pos, out);
    out << ", ";
  }

  // member: angule
  {
    out << "angule: ";
    rosidl_generator_traits::value_to_yaml(msg.angule, out);
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

  // member: input_voltage
  {
    out << "input_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.input_voltage, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MdRobotMsg2 & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: interval_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "interval_time: ";
    rosidl_generator_traits::value_to_yaml(msg.interval_time, out);
    out << "\n";
  }

  // member: x_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.x_pos, out);
    out << "\n";
  }

  // member: y_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.y_pos, out);
    out << "\n";
  }

  // member: angule
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angule: ";
    rosidl_generator_traits::value_to_yaml(msg.angule, out);
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

  // member: input_voltage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "input_voltage: ";
    rosidl_generator_traits::value_to_yaml(msg.input_voltage, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MdRobotMsg2 & msg, bool use_flow_style = false)
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
  const md::msg::MdRobotMsg2 & msg,
  std::ostream & out, size_t indentation = 0)
{
  md::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use md::msg::to_yaml() instead")]]
inline std::string to_yaml(const md::msg::MdRobotMsg2 & msg)
{
  return md::msg::to_yaml(msg);
}

template<>
inline const char * data_type<md::msg::MdRobotMsg2>()
{
  return "md::msg::MdRobotMsg2";
}

template<>
inline const char * name<md::msg::MdRobotMsg2>()
{
  return "md/msg/MdRobotMsg2";
}

template<>
struct has_fixed_size<md::msg::MdRobotMsg2>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<md::msg::MdRobotMsg2>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<md::msg::MdRobotMsg2>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MD__MSG__DETAIL__MD_ROBOT_MSG2__TRAITS_HPP_
