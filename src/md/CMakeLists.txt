cmake_minimum_required(VERSION 3.5)
project(md)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 의존성 찾기
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(serial REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# 메시지 생성
rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/MdRobotMsg1.msg"
  "msg/MdRobotMsg2.msg"
  "msg/Pose.msg"
  DEPENDENCIES std_msgs geometry_msgs builtin_interfaces
)

# 실행 파일 추가
add_executable(md_robot_node
  src/md_robot_node/main.cpp
  src/md_robot_node/com.cpp
  src/md_robot_node/robot.cpp
)


# 명시적으로 serial 라이브러리 링크 -> 빌드된 실행 파일(md_robot_node)에 특정 라이브러리를 링크하는 명령어
target_link_libraries(md_robot_node
  serial
  ${PROJECT_NAME}__rosidl_typesupport_cpp # rosidl_generate_interfaces명령으로 생성된 사용자 정의 메세지를 지원하는 C++ 라이브러리
  ${rosidl_typesupport_cpp_LIBRARIES}  # std_msgs::String 메시지 타입을 퍼블리셔나 구독자로 사용할 때 이 라이브러리가 필요
  ${SERIAL_LIBRARIES} # serial 라이브러리
)

# 헤더 파일 경로 설정 -> 컴파일러가 헤더 파일을 검색할 디렉토리를 지정하는 명령어
target_include_directories(md_robot_node
  PRIVATE
  ${serial_INCLUDE_DIRS} # serial 라이브러리 경로 추가
  ${CMAKE_BINARY_DIR}/md/rosidl_generator_cpp/md/msg # rosidl_generator_cpp 경로 추가
  ${CMAKE_CURRENT_SOURCE_DIR}/include  # md_robot_node 디렉토리 추가
)
# 메시지 빌드 의존성 추가
add_dependencies(md_robot_node
  ${PROJECT_NAME}__rosidl_typesupport_cpp
  ${PROJECT_NAME}__rosidl_generator_cpp
)
# 빌드 타겟 설정 - CMake에서 ament 빌드 시스템을 통해 패키지가 의존하는 모든 라이브러리나 패키지를 설정
ament_target_dependencies(md_robot_node
  rclcpp
  rclcpp_components
  std_msgs
  geometry_msgs
  sensor_msgs
  nav_msgs
  serial
  rosidl_default_runtime # 메세지 타입을 퍼블리셔/구독자에서 사용하기 위해 사용
)

# 설치 규칙
install(TARGETS md_robot_node
  DESTINATION lib/
)

install(DIRECTORY include/
  DESTINATION include/
)

install(DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# 패키지 설정
ament_export_dependencies(rosidl_default_runtime)
ament_package()
