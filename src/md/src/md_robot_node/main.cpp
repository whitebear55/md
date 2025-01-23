#include <rclcpp/rclcpp.hpp>
#include "md_robot_node/main.hpp"
#include "md_robot_node/global.hpp"
#include "md_robot_node/robot.hpp" // 로봇 헤더를 포함

#define MAX_CONNECTION_CHECK_COUNT              10

MDRobotNode::MDRobotNode():Node("md_robot_node")
{
    byCntInitStep = SETTING_PARAM_STEP_PID_PNT_VEL_CMD; // 모터 초기화 변수
    reset_pos_flag_=false;
    reset_alarm_flag_=false;

    remote_pc_connection_state = false;
    mdui_mdt_connection_state = false;

    fgInitsetting = INIT_SETTING_STATE_NONE; // 연결 상태 변수 정의

    check_connection_retry_count = 0;
    byCntComStep = 0;

    robotParamData.nIDPC = MID_REMOTE_PC;         // Platform mini-PC ID
    robotParamData.nIDMDUI = MID_MDUI;       // MDUI ID
    robotParamData.nIDMDT = MID_MDT;        // MD750T, MD400T, MD200T ID
    

    if(robotParamData.use_MDUI == 1) 
    { robotParamData.nRMID = robotParamData.nIDMDUI;}
    else 
    {robotParamData.nRMID = robotParamData.nIDMDT;}
    RCLCPP_ERROR(this->get_logger(), "robotParamData.nIDPC : %d", robotParamData.nIDPC);
    RCLCPP_ERROR(this->get_logger(), "robotParamData.nRMID : %d", robotParamData.nRMID);
    
    declare_parameters();
    get_parameters();

    // Publisher
    md_robot_message1_pub_ = this->create_publisher<md::msg::MdRobotMsg1>("md_robot_message1", 10);
    md_robot_message2_pub_ = this->create_publisher<md::msg::MdRobotMsg2>("md_robot_message2", 10);
    md_robot_status_msg_pub_ = this->create_publisher<md::msg::Pose>("robot_status", 10);

    // Subscriber
    cmd_vel_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
        "cmd_vel", 10, std::bind(&MDRobotNode::cmdVelCallback, this, std::placeholders::_1));

    reset_position_sub_ = this->create_subscription<std_msgs::msg::Bool>(
        "reset_position", 10, std::bind(&MDRobotNode::resetPositionCallback, this, std::placeholders::_1));
    
    reset_alarm_sub_ = this->create_subscription<std_msgs::msg::Bool>(
        "reset_alarm", 10, std::bind(&MDRobotNode::resetAlarmCallback, this, std::placeholders::_1));

    // Timer
    vel_cmd_rcv_timeout_timer_ = this->create_wall_timer(
        std::chrono::seconds(1), std::bind(&MDRobotNode::VelCmdRcvTimeoutCallback, this));
    status_request_timer_ = this->create_wall_timer(
        std::chrono::milliseconds(100), std::bind(&MDRobotNode::RequestRobotStatus, this));
    receive_data_timer_ = this->create_wall_timer(
        std::chrono::milliseconds(100), std::bind(&MDRobotNode::timerCallback, this));

    // Initialize communication
    if (InitSerialComm() == -1) {
        RCLCPP_ERROR(this->get_logger(), "Failed to initialize serial communication.");
        rclcpp::shutdown();
    }
    robotParamData.nDiameter = static_cast<int>(robotParamData.wheel_radius * 2.0 * 1000.0);
    robotParamData.degree_per_encoder_count = 360/robotParamData.encoder_PPR;
    InitMotorParameterLoop();
}

void MDRobotNode::declare_parameters() {
    this->declare_parameter("serial_port", "ttyUSB0");
    this->declare_parameter("serial_baudrate", 57600);
    this->declare_parameter("reverse_direction", 0);
    this->declare_parameter("maxrpm", 1000);
    this->declare_parameter("enable_encoder", 0);
    this->declare_parameter("slow_start", 300);
    this->declare_parameter("slow_down", 300);
    this->declare_parameter("wheel_length", 0.454);
    this->declare_parameter("reduction", 30);
    this->declare_parameter("wheel_radius", 0.0935);
    this->declare_parameter("encoder_PPR", 900);
}

void MDRobotNode::get_parameters() {
    this->get_parameter("serial_port", serial_port);
    this->get_parameter("serial_baudrate", robotParamData.nBaudrate);
    this->get_parameter("reverse_direction", robotParamData.reverse_direction);
    this->get_parameter("maxrpm", robotParamData.nMaxRPM);
    this->get_parameter("enable_encoder", robotParamData.enable_encoder);
    this->get_parameter("slow_start", robotParamData.nSlowstart);
    this->get_parameter("slow_down", robotParamData.nSlowdown);
    this->get_parameter("wheel_length", robotParamData.nWheelLength);
    this->get_parameter("reduction", robotParamData.nGearRatio);
    this->get_parameter("wheel_radius", robotParamData.wheel_radius);
    this->get_parameter("encoder_PPR", robotParamData.encoder_PPR);
}

void MDRobotNode::cmdVelCallback(const geometry_msgs::msg::Twist::SharedPtr msg) {
    velCmdRcvCount++;
    goal_cmd_speed = msg->linear.x;
    goal_cmd_ang_speed = msg->angular.z;
}

void MDRobotNode::resetPositionCallback(const std_msgs::msg::Bool::SharedPtr msg) {
    if (msg->data) {
        reset_pos_flag_ = true;
    }
}

void MDRobotNode::resetAlarmCallback(const std_msgs::msg::Bool::SharedPtr msg) {
    if (msg->data) {
        reset_alarm_flag_ = true;
    }
}
void MDRobotNode::timerCallback() {
    // ReceiveSerialData 함수 호출
    ReceiveSerialData(*this);  // 'this'는 현재 MDRobotNode 객체
}

void MDRobotNode::VelCmdRcvTimeoutCallback()
{
    static uint32_t old_velCmdRcvCount;

    if(velCmdRcvCount == old_velCmdRcvCount) 
    {
        goal_cmd_speed = 0;
        goal_cmd_ang_speed = 0;
    }
    
    else
    {
        if(remote_pc_connection_state == true)
        {
            velCmdUpdateCount++;
        }
    }
    old_velCmdRcvCount = velCmdRcvCount;
}

void MDRobotNode::InitMotorParameter()               // If using MDUI
{
    switch(byCntInitStep)
    {
        case SETTING_PARAM_STEP_PID_PNT_VEL_CMD:
        {
            PID_PNT_VEL_CMD_t cmd_data, *p;

#if 1
            RCLCPP_INFO(this->get_logger(),"[SET] PID_PNT_VEL_CMD(PID NO: %d)", PID_PNT_VEL_CMD);
            // ROS_INFO("size of PID_PNT_VEL_CMD_t: %ld", sizeof(PID_PNT_VEL_CMD_t));
#endif

            p = &cmd_data;
            p->enable_id1 = 1;
            p->rpm_id1 = 0;
            p->enable_id2 = 1;
            p->rpm_id2 = 0;

            if(robotParamData.use_MDUI == 1) {              // Use only if you use MDUI
                p->req_monitor_id = REQUEST_PID_ROBOT_MONITOR;
            }
            else {
                p->req_monitor_id = REQUEST_PNT_MAIN_DATA;
            }

            pid_response_receive_count = 0;
            pid_request_cmd_vel_count = 1;

            PutMdData(*this,PID_PNT_VEL_CMD, robotParamData.nRMID, (const uint8_t *)&cmd_data, sizeof(cmd_data));

            byCntInitStep = SETTING_PARAM_WAIT;
            break;
        }

        case SETTING_PARAM_WAIT:
        {
            if(pid_response_receive_count > 0) {
                pid_response_receive_count = 0;
                byCntInitStep = SETTING_PARAM_STEP_PID_ROBOT_PARAM;
            }

            else {
                check_connection_retry_count++;
                if(check_connection_retry_count >= MAX_CONNECTION_CHECK_COUNT) {
                    RCLCPP_INFO(this->get_logger(),"!!! Error RS232(MDUI) or RS485(MDT) !!!");
                    fgInitsetting = INIT_SETTING_STATE_ERROR;
                    byCntInitStep = SETTING_PARAM_STEP_DONE;
                }
                else {
                    byCntInitStep = SETTING_PARAM_STEP_PID_PNT_VEL_CMD;
                }
            }
            break;
        }

        case SETTING_PARAM_STEP_PID_ROBOT_PARAM:
        {
            if(robotParamData.use_MDUI == 1) {              // Use only if you use MDUI
                PID_ROBOT_PARAM_t cmd_data, *p;

#if 1
                RCLCPP_INFO(this->get_logger(),"[SET] SETTING_PARAM_STEP_PID_ROBOT_PARAM(PID NO: %d)", SETTING_PARAM_STEP_PID_ROBOT_PARAM);
                // RCLCPP_INFO(this->get_logger(),"size of PID_ROBOT_PARAM_t: %ld", sizeof(c));
#endif
                p = &cmd_data;
                p->nDiameter = (uint16_t)robotParamData.nDiameter;
                p->nWheelLength = (uint16_t)(robotParamData.nWheelLength * 1000.0);                 // m unit --> mm unit
                p->nGearRatio = (uint16_t)robotParamData.nGearRatio;

                RCLCPP_INFO(this->get_logger(),"D: %d, L: %d, R: %d", p->nDiameter, p->nWheelLength, p->nGearRatio);
                
                PutMdData(*this,PID_ROBOT_PARAM, MID_MDUI, (const uint8_t *)p, sizeof(cmd_data));     // 247
            }

            byCntInitStep = SETTING_PARAM_STEP_PID_POSI_RESET;
            break;
        }

        case SETTING_PARAM_STEP_PID_POSI_RESET:
        {
            uint8_t dummy;

#if 1
            RCLCPP_INFO(this->get_logger(),"[SET] PID_POSI_RESET(PID NO: %d)", PID_POSI_RESET);
#endif

            dummy = 0;
            PutMdData(*this,PID_POSI_RESET, robotParamData.nRMID, (const uint8_t *)&dummy, sizeof(dummy));

            byCntInitStep = SETTING_PARAM_STEP_PID_SLOW_START;
            break;
        }

        case SETTING_PARAM_STEP_PID_SLOW_START:
        {
            PID_SLOW_START_t cmd_data, *p;

#if 1
            RCLCPP_INFO(this->get_logger(),"[SET] PID_SLOW_START(PID NO: %d)", PID_SLOW_START);
#endif

            p = &cmd_data;
            p->value = robotParamData.nSlowstart;

            PutMdData(*this,PID_SLOW_START, robotParamData.nRMID, (const uint8_t *)p, sizeof(cmd_data));

            byCntInitStep = SETTING_PARAM_STEP_PID_SLOW_DOWN;
            break;
        }

        case SETTING_PARAM_STEP_PID_SLOW_DOWN:
        {
            PID_SLOW_DOWN_t cmd_data, *p;

#if 1
            RCLCPP_INFO(this->get_logger(),"[SET] PID_SLOW_DOWN(PID NO: %d)", PID_SLOW_DOWN);
#endif

            p = &cmd_data;
            p->value = robotParamData.nSlowdown;

            PutMdData(*this,PID_SLOW_DOWN, robotParamData.nRMID, (const uint8_t *)p, sizeof(cmd_data));

            byCntInitStep = SETTING_PARAM_STEP_PID_INV_SIGH_CMD;
            break;
        }

        case SETTING_PARAM_STEP_PID_INV_SIGH_CMD:       // Left motor direction
        {
            uint8_t cmd_data;

#if 1
            RCLCPP_INFO(this->get_logger(),"[SET] PID_INV_SIGN_CMD(PID NO: %d)", PID_INV_SIGN_CMD);
#endif

            if(robotParamData.reverse_direction == 0) {
                cmd_data = 1;
            }
            else {
                cmd_data = 0;
            }

            PutMdData(*this,PID_INV_SIGN_CMD, robotParamData.nRMID, (const uint8_t *)&cmd_data, 1);

            byCntInitStep = SETTING_PARAM_STEP_PID_INV_SIGH_CMD2;
            break;
        }

        case SETTING_PARAM_STEP_PID_INV_SIGH_CMD2:      // Right motor direction
        {
            uint8_t cmd_data;

#if 1
            RCLCPP_INFO(this->get_logger(),"[SET] PID_INV_SIGN_CMD2(PID NO: %d)", PID_INV_SIGN_CMD2);
#endif

            if(robotParamData.reverse_direction == 0) {
                cmd_data = 0;
            }
            else {
                cmd_data = 1;
            }

            PutMdData(*this,PID_INV_SIGN_CMD2, robotParamData.nRMID, (const uint8_t *)&cmd_data, 1);

            byCntInitStep = SETTING_PARAM_STEP_PID_USE_EPOSI;
            break;
        }

        case SETTING_PARAM_STEP_PID_USE_EPOSI:
        {
            uint8_t cmd_data;

#if 1
            RCLCPP_INFO(this->get_logger(),"[SET] PID_USE_POSI(PID NO: %d)", PID_USE_POSI);
#endif

            // Encoder function: Use the encoder only when using an in-wheel motor
            if(robotParamData.enable_encoder == 0) {                // disable encoder
                cmd_data = 0;               // hall sensor
            }
            else {                                                  // enable encoder
                cmd_data = 1;               // encoder
            }

            PutMdData(*this,PID_USE_POSI, robotParamData.nRMID, (const uint8_t *)&cmd_data, 1);

            byCntInitStep = SETTING_PARAM_STEP_PID_PPR;
            break;
        }

        case SETTING_PARAM_STEP_PID_PPR:
        {
            // Use the encoder only when using an in-wheel motor
            if(robotParamData.use_MDUI == 1 && robotParamData.enable_encoder == 1) {              // Use only if you use MDUI
                PID_PPR_t cmd_data, *p;

#if 1
                RCLCPP_INFO(this->get_logger(),"[SET] PID_PPR(PID NO: %d)", PID_PPR);
#endif
                p = &cmd_data;

                p->PPR = robotParamData.encoder_PPR;

                PutMdData(*this,PID_PPR, robotParamData.nRMID, (const uint8_t *)&cmd_data, sizeof(PID_PPR_t));
            }

            byCntInitStep = SETTING_PARAM_STEP_DONE;

            if(pid_request_cmd_vel_count == 2) {
                fgInitsetting = INIT_SETTING_STATE_OK;
            }
            else {
                fgInitsetting = INIT_SETTING_STATE_ERROR;

                if(robotParamData.use_MDUI == 1) {
                    RCLCPP_INFO(this->get_logger(),"!!! Error RS232 interface !!!");
                }
                else {
                    RCLCPP_INFO(this->get_logger(),"!!! Error RS485 interface !!!");
                }
            }
            break;
        }

        default:
            break;
    }
}
void MDRobotNode::InitMotorParameterLoop() 
{
        rclcpp::Rate loop_rate(10); // 10 Hz
        // RCLCPP_INFO(this->get_logger(), "Initializing motor parameters... Initializing motor parameters...Initializing motor parameters...Initializing motor parameters...Initializing motor parameters...Initializing motor parameters...Initializing motor parameters...");
        while (rclcpp::ok()) {
            ReceiveSerialData(*this); // 데이터를 수신

            InitMotorParameter(); // 모터 파라미터 초기화

            if (fgInitsetting != INIT_SETTING_STATE_NONE) {
                RCLCPP_INFO(this->get_logger(), "Motor initialization complete.");
                break; // 초기화가 완료되면 루프 종료
            }

            rclcpp::spin_some(this->get_node_base_interface());
            loop_rate.sleep(); // 루프 주기 제어
        }

         RCLCPP_INFO(this->get_logger(), "Motor Status : %d", fgInitsetting);

        if (fgInitsetting == INIT_SETTING_STATE_OK) 
        {
            RCLCPP_INFO(this->get_logger(), "Motor initialization successful.");
            mdui_mdt_connection_state = true;
        } 
        else 
        {
            RCLCPP_ERROR(this->get_logger(), "Motor initialization failed.");
            rclcpp::shutdown();
        }
}

void MDRobotNode::RequestRobotStatus()
{
    int nArray[5];
    uint8_t req_pid;
    int16_t *pGoalRPMSpeed;

    switch(byCntComStep)
    {
        case 0:
        {
            // RCLCPP_INFO(this->get_logger(),"REQ: PID_PNT_VEL_CMD & PID_PNT_MAIN_DATA");
            if(velCmdUpdateCount > 0) 
            {
                
                velCmdUpdateCount = 0;

                PID_PNT_VEL_CMD_t pid_pnt_vel_cmd, *p;


                if(mdui_mdt_connection_state == true) {
                    pGoalRPMSpeed = RobotSpeedToRPMSpeed(*this,goal_cmd_speed, goal_cmd_ang_speed);
                    
                }
                else {
                    pGoalRPMSpeed[0] = 0;
                    pGoalRPMSpeed[1] = 0;
                }

#if 1
                RCLCPP_INFO(this->get_logger(),"Goal %.2f, %.2f, RPM L:%d, R:%d", goal_cmd_speed, goal_cmd_ang_speed, pGoalRPMSpeed[0], pGoalRPMSpeed[1]);
#endif

                p = &pid_pnt_vel_cmd;
                p->enable_id1 = 1;
                p->rpm_id1 = pGoalRPMSpeed[0];
                p->enable_id2 = 1;
                p->rpm_id2 = pGoalRPMSpeed[1];

                if(robotParamData.use_MDUI == 1) {              // Use only if you use MDUI
                    p->req_monitor_id = REQUEST_PID_ROBOT_MONITOR;
                }
                else {
                    p->req_monitor_id = REQUEST_PNT_MAIN_DATA;
                }

                PutMdData(*this,PID_PNT_VEL_CMD, robotParamData.nRMID, (const uint8_t *)&pid_pnt_vel_cmd, sizeof(pid_pnt_vel_cmd));

                RCLCPP_INFO(this->get_logger(),"PID_MAIN_DATA");
                
                pid_request_cmd_vel_count++;
            }

            if(robotParamData.use_MDUI == 1) {              // Use only if you use MDUI
                if(curr_pid_robot_monitor.byPlatStatus.bits.bEmerSW == 1)
                {
                    byCntComStep = 3;
                    break;
                }
            }

            if(reset_pos_flag_ == true || reset_alarm_flag_ == true) {
                byCntComStep = 3;
                break;
            }
            else {
                byCntComStep = 4;
                break;
            }
            break;
        }

        case 3:
        {
            if(robotParamData.use_MDUI == 1) {              // Use only if you use MDUI
                if(curr_pid_robot_monitor.byPlatStatus.bits.bEmerSW == 1)
                {
                    PID_PNT_TQ_OFF_t pid_pnt_tq_off, *p;

                    pid_pnt_tq_off.enable_id1 = 1;
                    pid_pnt_tq_off.enable_id2 = 1;
                    pid_pnt_tq_off.req_monitor_id = REQUEST_PNT_MAIN_DATA;
                    PutMdData(*this,PID_PNT_TQ_OFF, robotParamData.nRMID, (const uint8_t *)&pid_pnt_tq_off, sizeof(pid_pnt_tq_off));
                }
            }
            
            if(reset_pos_flag_ == true) {
                uint8_t dummy;  
                
                reset_pos_flag_ = false;

                dummy = 0;
                PutMdData(*this,PID_POSI_RESET, robotParamData.nRMID, (const uint8_t *)&dummy, sizeof(dummy));
            }
            else if(reset_alarm_flag_ == true) {
                uint8_t cmd_pid;

                reset_alarm_flag_ = false;

                cmd_pid = CMD_ALARM_RESET;
                PutMdData(*this,PID_COMMAND, robotParamData.nRMID, (const uint8_t *)&cmd_pid, 1);
            }

            byCntComStep = 0;
            break;
        }

        case 4:
        {
            uint8_t request_pid;  

            if(robotParamData.use_MDUI == 0) { 
                request_pid = PID_IO_MONITOR;

                // RCLCPP_INFO(this->get_logger(),"REQ: PID_IO_MONITOR");

                PutMdData(*this,PID_REQ_PID_DATA, robotParamData.nRMID, (const uint8_t *)&request_pid, 1);
            }
            else {
                request_pid = PID_ROBOT_MONITOR2;

                RCLCPP_INFO(this->get_logger(),"REQ: PID_ROBOT_MONITOR2");

                PutMdData(*this,PID_REQ_PID_DATA, robotParamData.nRMID, (const uint8_t *)&request_pid, 1);
            }

            byCntComStep = 0;
            break;
        }

        default:
            byCntComStep = 0;
            break;
    }
}

void MDRobotNode::PubRobotRPMMessage() {
    md_robot_message1_pub_->publish(md_robot_msg_pid_pnt_main_data);
}

void MDRobotNode::PubRobotOdomMessage() {
    md_robot_message2_pub_->publish(md_robot_msg_pid_robot_monitor);
}

void MDRobotNode::PubRobotStatusMessage() {
    md_robot_status_msg_pub_->publish(md_robot_status_msg);
}
int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MDRobotNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
