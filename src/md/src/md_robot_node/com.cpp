#include <rclcpp/rclcpp.hpp>
#include "md_robot_node/com.hpp"
#include "md_robot_node/main.hpp"     // MDRobotNode 정의가 포함된 파일을 포함
#include "md_robot_node/robot.hpp"     // MDRobotNode 정의가 포함된 파일을 포함
#include <serial/serial.h>
#include <cstring>

#define MD_PROTOCOL_POS_PID             3
#define MD_PROTOCOL_POS_DATA_LEN        4
#define MD_PROTOCOL_POS_DATA_START      5

#define ENABLE_SERIAL_DEBUG             0

// Serial communication 객체
serial::Serial ser;

uint8_t serial_comm_rcv_buff[MAX_PACKET_SIZE];
uint8_t serial_comm_snd_buff[MAX_PACKET_SIZE];

// 전역 변수 선언 (ROS 2 노드에서 사용 가능하도록 외부에서 정의)
extern INIT_SETTING_STATE_t fgInitsetting;
extern 

// ROS 2 기반의 초기화 함수
int MDRobotNode::InitSerialComm() {
    std::string port = "/dev/" + serial_port;

    RCLCPP_INFO(rclcpp::get_logger("com"), "Serial port: %s", port.c_str());
    RCLCPP_INFO(rclcpp::get_logger("com"), "Serial baudrate: %d", robotParamData.nBaudrate);

    try {
        ser.setPort(port);
        ser.setBaudrate(static_cast<uint32_t>(robotParamData.nBaudrate));
        serial::Timeout to = serial::Timeout::simpleTimeout(1667); // 1667 when baud is 57600, 0.6ms
        ser.setTimeout(to);                                        // 2857 when baud is 115200, 0.35ms
        ser.open();

    } catch (serial::IOException& e) {
        RCLCPP_ERROR(rclcpp::get_logger("com"), "Unable to open port : %s", e.what());
        return -1;
    }

    if (ser.isOpen()) {
        
        RCLCPP_INFO(rclcpp::get_logger("com"), "*Serial port open success!");
        remote_pc_connection_state = true;
        
        return 1;
    } 
    
    else {
        return -1;
    }
}

uint8_t CalCheckSum(uint8_t *pData, uint16_t length) {
    uint16_t sum = 0;
    for (int i = 0; i < length; i++) {
        sum += *pData++;
    }
    return ~sum + 1; // Checksum 계산
}

int PutMdData(MDRobotNode &node, PID_CMD_t pid, uint16_t rmid, const uint8_t *pData, uint16_t length) {
    uint8_t *p;
    uint16_t len = 0;

    serial_comm_snd_buff[len++] = rmid;
    serial_comm_snd_buff[len++] = node.getRobotParamData().nIDPC;
    serial_comm_snd_buff[len++] = 1;  // Protocol version
    serial_comm_snd_buff[len++] = static_cast<uint8_t>(pid);
    serial_comm_snd_buff[len++] = length;

    p = &serial_comm_snd_buff[len];
    memcpy(p, pData, length);
    len += length;

    serial_comm_snd_buff[len++] = CalCheckSum(serial_comm_snd_buff, len);

    if (ser.isOpen()) {
        ser.write(serial_comm_snd_buff, len);
    }

    return 1;
}

int MdReceiveProc(MDRobotNode &node) 
{
    uint8_t *pRcvBuf = serial_comm_rcv_buff;
    uint8_t *pRcvData = &pRcvBuf[MD_PROTOCOL_POS_DATA_START];
    uint8_t byRcvPID = pRcvBuf[MD_PROTOCOL_POS_PID];
    uint8_t byRcvDataSize = pRcvBuf[MD_PROTOCOL_POS_DATA_LEN];

    switch (byRcvPID) {
        case PID_IO_MONITOR:
            // RCLCPP_INFO(rclcpp::get_logger("com"), "RCV: PID_IO_MONITOR: %d, %d", byRcvDataSize, (int)sizeof(PID_IO_MONITOR_t));
            memcpy(&node.getCurrPidIoMonitor(), pRcvData, sizeof(PID_IO_MONITOR_t));
            // RCLCPP_INFO(rclcpp::get_logger("com"), "Input voltage: %d", node.getCurrPidIoMonitor().input_voltage);
            break;

        case PID_ROBOT_MONITOR2:
            RCLCPP_INFO(rclcpp::get_logger("com"), "RCV: PID_ROBOT_MONITOR2: %d, %d", byRcvDataSize, (int)sizeof(PID_ROBOT_MONITOR2_t));
            memcpy(&node.getCurrPidRobotMonitor2(), pRcvData, sizeof(PID_ROBOT_MONITOR2_t));
            RCLCPP_INFO(rclcpp::get_logger("com"), "Input voltage: %d", node.getCurrPidRobotMonitor2().sVoltIn);
            break;

        case PID_PNT_MAIN_DATA:
            if (byRcvDataSize == sizeof(PID_PNT_MAIN_DATA_t)) {
                RCLCPP_INFO(rclcpp::get_logger("com"), "왼쪽 엔코더 : %d, 오른쪽 엔코더  %d", node.getCurrPidMainData().mtr_pos_id1,node.getCurrPidMainData().mtr_pos_id2);

                node.incrementReceiveCount();
                node.setRequestCmdCount(2);

                memcpy((char *)&node.getCurrPidMainData(), (char *)pRcvData, sizeof(PID_PNT_MAIN_DATA_t));

                MakeMDRobot_Status_Message(node,&node.getCurrPidMainData());


                node.PubRobotRPMMessage();
            }
            break;

        case PID_ROBOT_MONITOR:
            if (byRcvDataSize == sizeof(PID_ROBOT_MONITOR_t)) {

                node.incrementReceiveCount();
                node.setRequestCmdCount(2);

                memcpy(&node.getCurrPidRobotMonitor(), pRcvData, sizeof(PID_ROBOT_MONITOR_t));

                MakeMDRobotMessage2(node,&node.getCurrPidRobotMonitor());


                node.PubRobotOdomMessage();
            }
            break;

        default:
            break;
    }

    return 1;
}

int AnalyzeReceivedData(MDRobotNode &node, uint8_t byArray[], uint8_t byBufNum) //Analyze the communication data
{
    rclcpp::Clock clock(RCL_SYSTEM_TIME);  // ROS2의 시계 객체
    rclcpp::Time stamp = clock.now();      // 현재 시간

    uint8_t i, j;
    uint8_t data;
    static uint8_t byChkSec;
    static long lExStampSec, lExStampNsec;
    static uint32_t byPacketNum;
    static uint32_t rcv_step;
    static uint8_t byChkSum;
    static uint16_t byMaxDataNum;
    static uint16_t byDataNum;

    // RCLCPP_INFO(node.get_logger(), "byPacketNum: %d", byPacketNum);

    if (byPacketNum >= MAX_PACKET_SIZE)
    {
        rcv_step = 0;
        byPacketNum = 0;

        return 0;
    }
    
    for (j = 0; j < byBufNum; j++)
    {
        data = byArray[j];
#if (ENABLE_SERIAL_DEBUG == 1)
        printf("%02x(%3d) ", data, data);
#endif
        // RCLCPP_INFO(node.get_logger(),"data : %d, nIDMDUI : %d, nIDMDT : %d",data, node.getRobotParamData().nIDMDUI,node.getRobotParamData().nIDMDT);
        switch (rcv_step)
        {
        case 0: // Put the reading machine id after checking the data
            if (data == node.getRobotParamData().nIDPC) // 172
            {
                // RCLCPP_INFO(node.get_logger(),"11111111111111");
                byPacketNum = 0;
                byChkSum = data;
                serial_comm_rcv_buff[byPacketNum++] = data;

                rcv_step++;
            }
            else
            {
                byPacketNum = 0;
#if (ENABLE_SERIAL_DEBUG == 1)
                RCLCPP_INFO(node.get_logger(), "received ID: %d(0x%02x)", data, data);
                RCLCPP_INFO(node.get_logger(), "error.ser: %s, %d", __FILE__, __LINE__);
#endif
            }
            break;
        
        case 1: // Put the transmitting machine id after checking the data
            if ((data == node.getRobotParamData().nIDMDUI) || (data == node.getRobotParamData().nIDMDT))
            {
                // RCLCPP_INFO(node.get_logger(),"22222222222222222");
                byChkSum += data;
                serial_comm_rcv_buff[byPacketNum++] = data;

                rcv_step++;
            }
            else
            {
                rcv_step = 0;
                byPacketNum = 0;
#if (ENABLE_SERIAL_DEBUG == 1)
                RCLCPP_INFO(node.get_logger(), "error.ser: %s, %d", __FILE__, __LINE__);
#endif
            }
            break;

        case 2: // Check ID
            if (data == 1 || data == ID_ALL)
            {
                // RCLCPP_INFO(node.get_logger(),"3333333333333333333");
                byChkSum += data;
                serial_comm_rcv_buff[byPacketNum++] = data;

                rcv_step++;
            }
            else
            {
                rcv_step = 0;
                byPacketNum = 0;
#if (ENABLE_SERIAL_DEBUG == 1)
                RCLCPP_INFO(node.get_logger(), "error.ser: %s, %d", __FILE__, __LINE__);
#endif
            }
            break;

        case 3: // Put the PID number into the array
            // RCLCPP_INFO(node.get_logger(),"44444444444444444444444");
            byChkSum += data;
            serial_comm_rcv_buff[byPacketNum++] = data;

            rcv_step++;
            break;

        case 4: // Put the DATANUM into the array
            // RCLCPP_INFO(node.get_logger(),"555555555555555555555");
            byChkSum += data;
            serial_comm_rcv_buff[byPacketNum++] = data;

            byMaxDataNum = data;
            byDataNum = 0;

            rcv_step++;
            break;

        case 5: // Put the DATA into the array
            // RCLCPP_INFO(node.get_logger(),"6666666666666666666666666666");
            byChkSum += data;
            serial_comm_rcv_buff[byPacketNum++] = data;

            if (++byDataNum >= MAX_DATA_SIZE)
            {
                rcv_step = 0;
#if (ENABLE_SERIAL_DEBUG == 1)
                RCLCPP_INFO(node.get_logger(), "error.ser: %s, %d", __FILE__, __LINE__);
#endif
                break;
            }

            if (byDataNum >= byMaxDataNum)
            {
                rcv_step++;
            }
            break;

        case 6: // Put the checksum after Checking checksum
            // RCLCPP_INFO(node.get_logger(),"7777777777777777777777");
            byChkSum += data;
            serial_comm_rcv_buff[byPacketNum++] = data;

            if (byChkSum == 0)
            {
#if (ENABLE_SERIAL_DEBUG == 1)
                printf("\r\n");
#endif
                MdReceiveProc(node); // Save the identified serial data to defined variable
            }
            else
            {
                RCLCPP_INFO(node.get_logger(), "Error.Checksum");
            }

            byPacketNum = 0;
            rcv_step = 0;
            break;

        default:
            rcv_step = 0;
            break;
        }
    }
    return 1;
}

int MDRobotNode::ReceiveSerialData(MDRobotNode &node) {
    uint8_t byRcvBuf[250];
    uint8_t byBufNumber = ser.available();

    // RCLCPP_INFO(node.get_logger(), "ReceiveSerialData: ############ ReceiveSerialDataReceiveSerialData");
    if (byBufNumber > 0) {
        if (byBufNumber > sizeof(byRcvBuf)) {
            byBufNumber = sizeof(byRcvBuf);
        }

        ser.read(byRcvBuf, byBufNumber);
        // RCLCPP_INFO(node.get_logger(), "First byte received: %d", byRcvBuf[0]);
        AnalyzeReceivedData(node, byRcvBuf, byBufNumber);
    }

    return 1;
}
