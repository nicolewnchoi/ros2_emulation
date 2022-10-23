cmake_minimum_required(VERSION 3.5)
project(ap_interfaces)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#set(SFML_DIR "${CMAKE_SOURCE_DIR}/library/SFML-2.5.1/lib/cmake/SFML")

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

find_package(rosidl_default_generators REQUIRED)
#find_package(OpenCV 4.3.0 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
#find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(msg_files
  "msg/Pos.msg"
  "msg/Score.msg"
  "msg/Button.msg"
)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Pos.msg"
  "msg/Score.msg"
  "msg/Button.msg"
  "srv/gameinfo.srv"
)


add_executable(player_detection src/player_detection.cpp)
ament_target_dependencies(player_detection OpenCV rclcpp std_msgs)
rosidl_target_interfaces(player_detection
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(rfid src/rfid.cpp)
ament_target_dependencies(rfid rclcpp std_msgs)
rosidl_target_interfaces(rfid
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(button src/button.cpp)
target_link_libraries(button sfml-graphics)
ament_target_dependencies(button rclcpp std_msgs)
rosidl_target_interfaces(button
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

add_executable(ui src/ui.cpp)
ament_target_dependencies(ui rclcpp std_msgs)
rosidl_target_interfaces(ui
  ${PROJECT_NAME} "rosidl_typesupport_cpp")

install(TARGETS
  player_detection
  rfid
  button
  ui
  DESTINATION lib/${PROJECT_NAME})


install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()