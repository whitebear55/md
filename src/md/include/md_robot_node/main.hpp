#pragma once
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <std_msgs/msg/bool.hpp>
#include "md/msg/md_robot_msg1.hpp"
#include "md/msg/md_robot_msg2.hpp"
#include "md/msg/pose.hpp"
#include "md_robot_node/global.hpp"

#define MAX_CONNECTION_CHECK_COUNT 10

//message
extern md::msg::MdRobotMsg1 md_robot_msg_pid_pnt_main_data;
extern md::msg::MdRobotMsg2 md_robot_msg_pid_robot_monitor;
extern md::msg::Pose md_robot_status_msg;  // 로봇 상태 메시지 객체

class MDRobotNode : public rclcpp::Node {
public:
    MDRobotNode();
    
    // Getter 함수들 추가
    ROBOT_PARAMETER_t& getRobotParamData() { return robotParamData; }
    PID_PNT_MAIN_DATA_t& getCurrPidMainData() { return curr_pid_pnt_main_data;}
    PID_IO_MONITOR_t& getCurrPidIoMonitor() { return curr_pid_io_monitor; }
    PID_ROBOT_MONITOR_t& getCurrPidRobotMonitor() { return curr_pid_robot_monitor;}
    PID_ROBOT_MONITOR2_t& getCurrPidRobotMonitor2() {return curr_pid_robot_monitor2;}

    // Setter 함수들 추가
    void incrementRequestCmdCount() { pid_request_cmd_vel_count++; }
    void incrementReceiveCount() { pid_response_receive_count++; }

    void setRequestCmdCount(int val) { pid_request_cmd_vel_count = val; }
    void setReceiveCount(int val) { pid_response_receive_count = val; }

    int getRequestCmdCount() { return pid_request_cmd_vel_count; }
    int getReceiveCount() { return pid_response_receive_count; }

    void timerCallback();
    void PubRobotRPMMessage();
    void PubRobotOdomMessage();
    void PubRobotStatusMessage();

    int ReceiveSerialData(MDRobotNode &node);

private:
    // Member variables
    bool reset_pos_flag_;
    bool reset_alarm_flag_;

    std::string serial_port;

    INIT_SETTING_STATE_t fgInitsetting;

    ROBOT_PARAMETER_t robotParamData;

    SETTINNG_PARAM_STEP_t byCntInitStep;

    uint16_t byCntComStep;
    uint32_t velCmdUpdateCount;
    uint32_t velCmdRcvCount;
    uint32_t pid_response_receive_count;
    uint32_t pid_request_cmd_vel_count;
    volatile bool mdui_mdt_connection_state;
    volatile bool remote_pc_connection_state;

    // 데이터 구조체 초기화
    PID_PNT_MAIN_DATA_t curr_pid_pnt_main_data;
    PID_IO_MONITOR_t curr_pid_io_monitor;
    PID_ROBOT_MONITOR_t curr_pid_robot_monitor;
    PID_ROBOT_MONITOR2_t curr_pid_robot_monitor2;

    uint16_t check_connection_retry_count;

    double goal_cmd_speed;             // m/sec
    double goal_cmd_ang_speed;         // radian/sec

    // Publishers
    rclcpp::Publisher<md::msg::MdRobotMsg1>::SharedPtr md_robot_message1_pub_;
    rclcpp::Publisher<md::msg::MdRobotMsg2>::SharedPtr md_robot_message2_pub_;
    rclcpp::Publisher<md::msg::Pose>::SharedPtr md_robot_status_msg_pub_;
    
    // Subscribers
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_sub_;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr reset_position_sub_;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr reset_alarm_sub_;

    // Timer
    rclcpp::TimerBase::SharedPtr vel_cmd_rcv_timeout_timer_;
    rclcpp::TimerBase::SharedPtr status_request_timer_;
    rclcpp::TimerBase::SharedPtr receive_data_timer_;  // Receive 데이터 타이머

    void declare_parameters();
    void get_parameters();
    void cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg); 
    void resetPositionCallback(const std_msgs::msg::Bool::SharedPtr msg);
    void resetAlarmCallback(const std_msgs::msg::Bool::SharedPtr msg);
    void VelCmdRcvTimeoutCallback();
    void InitMotorParameter();
    void InitMotorParameterLoop();
    void RequestRobotStatus();
    int InitSerialComm();
    
    
};

