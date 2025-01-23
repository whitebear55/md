// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from md:msg/MdRobotMsg1.idl
// generated code does not contain a copyright notice

#ifndef MD__MSG__DETAIL__MD_ROBOT_MSG1__TRAITS_HPP_
#define MD__MSG__DETAIL__MD_ROBOT_MSG1__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "md/msg/detail/md_robot_msg1__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace md
{

namespace msg
{

inline void to_flow_style_yaml(
  const MdRobotMsg1 & msg,
  std::ostream & out)
{
  out << "{";
  // member: interval_time
  {
    out << "interval_time: ";
    rosidl_generator_traits::value_to_yaml(msg.interval_time, out);
    out << ", ";
  }

  // member: motor1_rpm
  {
    out << "motor1_rpm: ";
    rosidl_generator_traits::value_to_yaml(msg.motor1_rpm, out);
    out << ", ";
  }

  // member: motor1_pos
  {
    out << "motor1_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.motor1_pos, out);
    out << ", ";
  }

  // member: motor2_rpm
  {
    out << "motor2_rpm: ";
    rosidl_generator_traits::value_to_yaml(msg.motor2_rpm, out);
    out << ", ";
  }

  // member: motor2_pos
  {
    out << "motor2_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.motor2_pos, out);
    out << ", ";
  }

  // member: motor1_state
  {
    out << "motor1_state: ";
    rosidl_generator_traits::value_to_yaml(msg.motor1_state, out);
    out << ", ";
  }

  // member: motor2_state
  {
    out << "motor2_state: ";
    rosidl_generator_traits::value_to_yaml(msg.motor2_state, out);
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
  const MdRobotMsg1 & msg,
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

  // member: motor1_rpm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor1_rpm: ";
    rosidl_generator_traits::value_to_yaml(msg.motor1_rpm, out);
    out << "\n";
  }

  // member: motor1_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor1_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.motor1_pos, out);
    out << "\n";
  }

  // member: motor2_rpm
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor2_rpm: ";
    rosidl_generator_traits::value_to_yaml(msg.motor2_rpm, out);
    out << "\n";
  }

  // member: motor2_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor2_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.motor2_pos, out);
    out << "\n";
  }

  // member: motor1_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor1_state: ";
    rosidl_generator_traits::value_to_yaml(msg.motor1_state, out);
    out << "\n";
  }

  // member: motor2_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor2_state: ";
    rosidl_generator_traits::value_to_yaml(msg.motor2_state, out);
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

inline std::string to_yaml(const MdRobotMsg1 & msg, bool use_flow_style = false)
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
  const md::msg::MdRobotMsg1 & msg,
  std::ostream & out, size_t indentation = 0)
{
  md::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use md::msg::to_yaml() instead")]]
inline std::string to_yaml(const md::msg::MdRobotMsg1 & msg)
{
  return md::msg::to_yaml(msg);
}

template<>
inline const char * data_type<md::msg::MdRobotMsg1>()
{
  return "md::msg::MdRobotMsg1";
}

template<>
inline const char * name<md::msg::MdRobotMsg1>()
{
  return "md/msg/MdRobotMsg1";
}

template<>
struct has_fixed_size<md::msg::MdRobotMsg1>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<md::msg::MdRobotMsg1>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<md::msg::MdRobotMsg1>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MD__MSG__DETAIL__MD_ROBOT_MSG1__TRAITS_HPP_
