cmake_minimum_required(VERSION 2.6)
project(pilot-base)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -pthread")

file(GLOB GENERATED_SOURCE_FILES generated/src/*.cpp)

if(WIN32)
	list(APPEND PLATFORM_SOURCE_FILES
		src/win32/SerialPort.cpp
		src/win32/Joystick.cpp
		src/win32/UDP_Receiver.cpp
	)
else()
	list(APPEND PLATFORM_SOURCE_FILES
		src/linux/SerialPort.cpp
		src/linux/Joystick.cpp
		src/linux/UDP_Receiver.cpp
	)
endif()

add_library(pilot_base SHARED
	${GENERATED_SOURCE_FILES}
	${PLATFORM_SOURCE_FILES}
	src/SerialPort.cpp
	src/CAN_Socket.cpp
	src/CAN_Frame.cpp
	src/CAN_Proxy.cpp
	src/Joystick.cpp
	src/UDP_Receiver.cpp
)

target_include_directories(pilot_base PUBLIC include generated/include)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY generated/include/ DESTINATION include)
install(DIRECTORY modules/ DESTINATION interface/pilot/base)
install(DIRECTORY interface/ DESTINATION interface/pilot/base)

install(TARGETS pilot_base DESTINATION lib)
