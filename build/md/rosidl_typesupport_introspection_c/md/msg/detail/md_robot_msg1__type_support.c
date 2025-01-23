// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from md:msg/MdRobotMsg1.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "md/msg/detail/md_robot_msg1__rosidl_typesupport_introspection_c.h"
#include "md/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "md/msg/detail/md_robot_msg1__functions.h"
#include "md/msg/detail/md_robot_msg1__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  md__msg__MdRobotMsg1__init(message_memory);
}

void md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_fini_function(void * message_memory)
{
  md__msg__MdRobotMsg1__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_message_member_array[8] = {
  {
    "interval_time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(md__msg__MdRobotMsg1, interval_time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor1_rpm",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(md__msg__MdRobotMsg1, motor1_rpm),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor1_pos",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(md__msg__MdRobotMsg1, motor1_pos),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor2_rpm",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(md__msg__MdRobotMsg1, motor2_rpm),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor2_pos",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(md__msg__MdRobotMsg1, motor2_pos),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor1_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(md__msg__MdRobotMsg1, motor1_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motor2_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(md__msg__MdRobotMsg1, motor2_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "input_voltage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(md__msg__MdRobotMsg1, input_voltage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_message_members = {
  "md__msg",  // message namespace
  "MdRobotMsg1",  // message name
  8,  // number of fields
  sizeof(md__msg__MdRobotMsg1),
  md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_message_member_array,  // message members
  md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_init_function,  // function to initialize message memory (memory has to be allocated)
  md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_message_type_support_handle = {
  0,
  &md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_md
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, md, msg, MdRobotMsg1)() {
  if (!md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_message_type_support_handle.typesupport_identifier) {
    md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &md__msg__MdRobotMsg1__rosidl_typesupport_introspection_c__MdRobotMsg1_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
