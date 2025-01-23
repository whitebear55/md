#pragma once

#include <rclcpp/rclcpp.hpp>
#include "md/msg/md_robot_msg1.hpp"  // MdRobotMsg1 메시지 타입
#include "md/msg/md_robot_msg2.hpp"  // MdRobotMsg2 메시지 타입
#include "md/msg/pose.hpp"
#include "md_robot_node/global.hpp"  // 전역 변수 및 구조체 정의
#include <cmath>
#include <memory>
class MDRobotNode;

extern md::msg::MdRobotMsg1 md_robot_msg_pid_pnt_main_data;  // MdRobotMsg1 메시지 객체
extern md::msg::MdRobotMsg2 md_robot_msg_pid_robot_monitor;  // MdRobotMsg2 메시지 객체
extern md::msg::Pose md_robot_status_msg;  // 로봇 상태 메시지 객체

// 함수 선언
int16_t *RobotSpeedToRPMSpeed(MDRobotNode &node,double linear, double angular);  // 속도 변환 함수

// Make 메시지 함수 선언
void MakeMDRobotMessage1(MDRobotNode &node,PID_PNT_MAIN_DATA_t *pData);  // MdRobotMsg1 메시지 생성
void MakeMDRobotMessage2(MDRobotNode &node,PID_ROBOT_MONITOR_t *pData);  // MdRobotMsg2 메시지 생성
void MakeMDRobot_Status_Message(MDRobotNode &node,PID_PNT_MAIN_DATA_t *pData);  // 로봇 상태 메시지 생성
std::unique_ptr<std::pair<std::array<double, 2>, double>> RPMToRobotSpeed(MDRobotNode &node, PID_PNT_MAIN_DATA_t *pData);
