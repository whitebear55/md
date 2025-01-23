// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from md:msg/MdRobotMsg1.idl
// generated code does not contain a copyright notice
#include "md/msg/detail/md_robot_msg1__rosidl_typesupport_fastrtps_cpp.hpp"
#include "md/msg/detail/md_robot_msg1__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace md
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_md
cdr_serialize(
  const md::msg::MdRobotMsg1 & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: interval_time
  cdr << ros_message.interval_time;
  // Member: motor1_rpm
  cdr << ros_message.motor1_rpm;
  // Member: motor1_pos
  cdr << ros_message.motor1_pos;
  // Member: motor2_rpm
  cdr << ros_message.motor2_rpm;
  // Member: motor2_pos
  cdr << ros_message.motor2_pos;
  // Member: motor1_state
  cdr << ros_message.motor1_state;
  // Member: motor2_state
  cdr << ros_message.motor2_state;
  // Member: input_voltage
  cdr << ros_message.input_voltage;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_md
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  md::msg::MdRobotMsg1 & ros_message)
{
  // Member: interval_time
  cdr >> ros_message.interval_time;

  // Member: motor1_rpm
  cdr >> ros_message.motor1_rpm;

  // Member: motor1_pos
  cdr >> ros_message.motor1_pos;

  // Member: motor2_rpm
  cdr >> ros_message.motor2_rpm;

  // Member: motor2_pos
  cdr >> ros_message.motor2_pos;

  // Member: motor1_state
  cdr >> ros_message.motor1_state;

  // Member: motor2_state
  cdr >> ros_message.motor2_state;

  // Member: input_voltage
  cdr >> ros_message.input_voltage;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_md
get_serialized_size(
  const md::msg::MdRobotMsg1 & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: interval_time
  {
    size_t item_size = sizeof(ros_message.interval_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: motor1_rpm
  {
    size_t item_size = sizeof(ros_message.motor1_rpm);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: motor1_pos
  {
    size_t item_size = sizeof(ros_message.motor1_pos);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: motor2_rpm
  {
    size_t item_size = sizeof(ros_message.motor2_rpm);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: motor2_pos
  {
    size_t item_size = sizeof(ros_message.motor2_pos);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: motor1_state
  {
    size_t item_size = sizeof(ros_message.motor1_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: motor2_state
  {
    size_t item_size = sizeof(ros_message.motor2_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: input_voltage
  {
    size_t item_size = sizeof(ros_message.input_voltage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_md
max_serialized_size_MdRobotMsg1(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: interval_time
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: motor1_rpm
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: motor1_pos
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: motor2_rpm
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: motor2_pos
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: motor1_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: motor2_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: input_voltage
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = md::msg::MdRobotMsg1;
    is_plain =
      (
      offsetof(DataType, input_voltage) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _MdRobotMsg1__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const md::msg::MdRobotMsg1 *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _MdRobotMsg1__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<md::msg::MdRobotMsg1 *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _MdRobotMsg1__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const md::msg::MdRobotMsg1 *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _MdRobotMsg1__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_MdRobotMsg1(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _MdRobotMsg1__callbacks = {
  "md::msg",
  "MdRobotMsg1",
  _MdRobotMsg1__cdr_serialize,
  _MdRobotMsg1__cdr_deserialize,
  _MdRobotMsg1__get_serialized_size,
  _MdRobotMsg1__max_serialized_size
};

static rosidl_message_type_support_t _MdRobotMsg1__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_MdRobotMsg1__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace md

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_md
const rosidl_message_type_support_t *
get_message_type_support_handle<md::msg::MdRobotMsg1>()
{
  return &md::msg::typesupport_fastrtps_cpp::_MdRobotMsg1__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, md, msg, MdRobotMsg1)() {
  return &md::msg::typesupport_fastrtps_cpp::_MdRobotMsg1__handle;
}

#ifdef __cplusplus
}
#endif
