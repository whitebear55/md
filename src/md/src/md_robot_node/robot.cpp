#include "md_robot_node/robot.hpp"
#include "md_robot_node/main.hpp"
#include "md/msg/pose.hpp"
#define ENABLE_MD_MESSAGE 

#define VELOCITY_CONSTANT_VALUE         9.5492743       // linear speed(m/min), v = the length of circle of wheel x RPM
                                                        // linear speed(m/sec), v = (2 x wheel radius x (pi / 60) x RPM)
                                                        // 0.10472 = (2 x pi / 60)
                                                        // V = r * w = r * (RPM * 0.10472)
                                                        //           = r * RPM * 0.10472
                                                        // RPM = V / r * 9.5492743

#define constrain(amt,low,high) ((amt)<=(low)?(low):((amt)>=(high)?(high):(amt)))

#define LEFT           	  0      // Swing direction
#define RIGHT             1

extern PID_PNT_MAIN_DATA_t curr_pid_pnt_main_data;
extern PID_ROBOT_MONITOR_t curr_pid_robot_monitor;
extern PID_ROBOT_MONITOR2_t curr_pid_robot_monitor2;
extern PID_IO_MONITOR_t curr_pid_io_monitor;


md::msg::MdRobotMsg1 md_robot_msg_pid_pnt_main_data;
md::msg::MdRobotMsg2 md_robot_msg_pid_robot_monitor;
md::msg::Pose md_robot_status_msg;


// m/sec --> RPM
int16_t *RobotSpeedToRPMSpeed(MDRobotNode &node,double linear, double angular) {

    double wheel_radius = node.getRobotParamData().wheel_radius;
    double wheel_separation = node.getRobotParamData().nWheelLength;
    double reduction = static_cast<double>(node.getRobotParamData().nGearRatio);
    double wheel_velocity_cmd[2];
    static int16_t goal_rpm_speed[2];

    // Calculate wheel velocity commands
    wheel_velocity_cmd[LEFT] = linear - (angular * wheel_separation / 2);
    wheel_velocity_cmd[RIGHT] = linear + (angular * wheel_separation / 2);

    // Convert linear velocity to RPM
    wheel_velocity_cmd[LEFT] = constrain(wheel_velocity_cmd[LEFT] * VELOCITY_CONSTANT_VALUE / wheel_radius * reduction, -node.getRobotParamData().nMaxRPM, node.getRobotParamData().nMaxRPM);
    wheel_velocity_cmd[RIGHT] = constrain(wheel_velocity_cmd[RIGHT] * VELOCITY_CONSTANT_VALUE / wheel_radius * reduction, -node.getRobotParamData().nMaxRPM, node.getRobotParamData().nMaxRPM);

    goal_rpm_speed[0] = static_cast<int16_t>(wheel_velocity_cmd[LEFT]);
    goal_rpm_speed[1] = static_cast<int16_t>(wheel_velocity_cmd[RIGHT]);

    return goal_rpm_speed;
}

std::unique_ptr<std::pair<std::array<double, 2>, double>> RPMToRobotSpeed(MDRobotNode &node, PID_PNT_MAIN_DATA_t *pData) {

    double wheel_radius = node.getRobotParamData().wheel_radius;
    double wheel_separation = node.getRobotParamData().nWheelLength;

    std::array<double, 2> linear_vel;
    double angular_vel;

    // linear velocity (m/s)
    linear_vel[LEFT] = pData->rpm_id1 * 2 * M_PI * wheel_radius / 60;  // left wheel speed
    linear_vel[RIGHT] = pData->rpm_id2 * 2 * M_PI * wheel_radius / 60;  // right wheel speed

    // angular velocity (rad/s)
    angular_vel = (linear_vel[RIGHT] - linear_vel[LEFT]) / wheel_separation;

    // Return linear velocities and angular velocity
    auto result = std::make_unique<std::pair<std::array<double, 2>, double>>(linear_vel, angular_vel);
    return result;
}

void MakeMDRobot_Status_Message(MDRobotNode &node, PID_PNT_MAIN_DATA_t *pData) {
    static bool first_cal = false;

    static rclcpp::Clock clock(RCL_SYSTEM_TIME); // rclcpp::Clock 객체를 하나만 생성
    static rclcpp::Time previous_time(0, 0, RCL_SYSTEM_TIME); // 이전 시간 초기화
    double interval_time;

    // 현재 시간과 이전 시간의 차이를 계산하여 시간 차이(interval_time) 계산
    rclcpp::Time curr_time = clock.now();
    interval_time = (curr_time - previous_time).seconds();
    previous_time = curr_time; // 이전 시간 갱신

    float robot_curr_x;
    float robot_curr_y;
    float robot_curr_theta;
    
    static double robot_old_x = 0;
    static double robot_old_y = 0;
    static double robot_old_theta = 0;

    static int old_mtr_pos_id1 = 0;
    static int old_mtr_pos_id2 = 0;

    // 엔코더 위치 값 계산
    int32_t pos_left = pData->mtr_pos_id1;
    int32_t pos_right = pData->mtr_pos_id2;

    double v_left = (double)(pos_left - old_mtr_pos_id1);  // 왼쪽 엔코더 카운트 값
    double v_right = (double)(pos_right - old_mtr_pos_id2); // 오른쪽 엔코더 카운트 값

    // 엔코더 카운트 값을 각도로 변환
    v_left *= node.getRobotParamData().degree_per_encoder_count;
    v_right *= node.getRobotParamData().degree_per_encoder_count;

    // RPM에서 로봇의 선형 속도와 각속도를 계산
    auto result = RPMToRobotSpeed(node, pData);
    float linear_vel = (result->first[LEFT] + result->first[RIGHT]) / 2.0;
    float angular_vel = result->second;

    // 각도와 위치 업데이트
    robot_curr_theta = robot_old_theta + angular_vel * interval_time;
    robot_curr_x = robot_old_x + (interval_time * linear_vel) * cos((long double)(robot_curr_theta));
    robot_curr_y = robot_old_y + (interval_time * linear_vel) * sin((long double)(robot_curr_theta));

    // 로봇 상태 메시지에 값 저장
    md_robot_status_msg.x = robot_curr_x;
    md_robot_status_msg.y = robot_curr_y;
    md_robot_status_msg.theta = robot_curr_theta;
    md_robot_status_msg.linear_velocity = linear_vel;
    md_robot_status_msg.angular_velocity = angular_vel;

    // 로그로 결과 출력
    RCLCPP_INFO(rclcpp::get_logger("com"),
                "Interval time: %f, x: %f, y: %f, theta: %f, linear velocity: %f, angular velocity: %f",
                interval_time, robot_curr_x, robot_curr_y, robot_curr_theta, linear_vel, angular_vel);

    // 이전 위치 값 갱신
    robot_old_x = robot_curr_x;
    robot_old_y = robot_curr_y;
    robot_old_theta = robot_curr_theta;

    // 엔코더 값 갱신
    old_mtr_pos_id1 = pos_left;
    old_mtr_pos_id2 = pos_right;
}
// 세타만 각도 처리하고 방향만 처리해라

// Create MdRobotMsg1
void MakeMDRobotMessage1(MDRobotNode &node,PID_PNT_MAIN_DATA_t *pData) {
    static bool first_cal = false;
    static rclcpp::Clock clock(RCL_SYSTEM_TIME); // rclcpp::Clock 객체를 하나만 생성
    static rclcpp::Time previous_time(0, 0, RCL_SYSTEM_TIME); // 이전 시간 초기화
    double interval_time;

    rclcpp::Time curr_time = clock.now(); // 현재 시간 가져오기
    interval_time = (curr_time - previous_time).seconds(); // 시간 차이 계산
    previous_time = curr_time; // 이전 시간 갱신

    // Fill message
    md_robot_msg_pid_pnt_main_data.interval_time = interval_time;
    md_robot_msg_pid_pnt_main_data.motor1_pos = pData->mtr_pos_id1;
    md_robot_msg_pid_pnt_main_data.motor2_pos = pData->mtr_pos_id2;
    md_robot_msg_pid_pnt_main_data.motor1_rpm = pData->rpm_id1;
    md_robot_msg_pid_pnt_main_data.motor2_rpm = pData->rpm_id2;

    md_robot_msg_pid_pnt_main_data.motor1_state = pData->mtr_state_id1.val;
    md_robot_msg_pid_pnt_main_data.motor2_state = pData->mtr_state_id2.val;

    md_robot_msg_pid_pnt_main_data.input_voltage = static_cast<float>(node.getCurrPidIoMonitor().input_voltage / 10.0);

#ifdef ENABLE_MD_MESSAGE
    RCLCPP_INFO(rclcpp::get_logger("robot"),
                "Interval time1: %f, pos1: %d, pos2: %d, rpm1: %d, rpm2: %d, input voltage: %f",
                interval_time,
                md_robot_msg_pid_pnt_main_data.motor1_pos,
                md_robot_msg_pid_pnt_main_data.motor2_pos,
                md_robot_msg_pid_pnt_main_data.motor1_rpm,
                md_robot_msg_pid_pnt_main_data.motor2_rpm,
                md_robot_msg_pid_pnt_main_data.input_voltage);
#endif
}

// Create MdRobotMsg2
void MakeMDRobotMessage2(MDRobotNode &node,PID_ROBOT_MONITOR_t *pData) {
    static bool first_cal = false;
    static rclcpp::Clock clock(RCL_SYSTEM_TIME); // rclcpp::Clock 객체를 하나만 생성
    static rclcpp::Time previous_time(0, 0, RCL_SYSTEM_TIME); // 이전 시간 초기화
    double interval_time;

    rclcpp::Time curr_time = clock.now(); // 현재 시간 가져오기
    interval_time = (curr_time - previous_time).seconds(); // 시간 차이 계산
    previous_time = curr_time; // 이전 시간 갱신

    // Fill message
    md_robot_msg_pid_robot_monitor.interval_time = interval_time;
    md_robot_msg_pid_robot_monitor.x_pos = pData->lTempPosi_x;
    md_robot_msg_pid_robot_monitor.y_pos = pData->lTempPosi_y;
    md_robot_msg_pid_robot_monitor.angule = pData->sTempTheta;

    if (node.getRobotParamData().reverse_direction == 0) {
        md_robot_msg_pid_robot_monitor.us_1 = pData->byUS1;
        md_robot_msg_pid_robot_monitor.us_2 = pData->byUS2;
    } else {
        md_robot_msg_pid_robot_monitor.us_1 = pData->byUS2;
        md_robot_msg_pid_robot_monitor.us_2 = pData->byUS1;
    }

    md_robot_msg_pid_robot_monitor.platform_state = pData->byPlatStatus.val;
    md_robot_msg_pid_robot_monitor.linear_velocity = pData->linear_velocity;
    md_robot_msg_pid_robot_monitor.angular_velocity = pData->angular_velocity;
    md_robot_msg_pid_robot_monitor.input_voltage = static_cast<float>(node.getCurrPidRobotMonitor2().sVoltIn / 10.0);

#ifdef ENABLE_MD_MESSAGE
    RCLCPP_INFO(rclcpp::get_logger("robot"),
                "Interval time2: %f, input_voltage: %f",
                interval_time, md_robot_msg_pid_robot_monitor.input_voltage);
#endif
}
