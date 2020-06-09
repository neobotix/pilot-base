cmake_minimum_required(VERSION 2.6)
project(pilot-sensors)

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

add_library(pilot_sensors SHARED
	${GENERATED_SOURCE_FILES}
	${PLATFORM_SOURCE_FILES}
	src/SerialPort.cpp
	src/Joystick.cpp
	src/SickS300.cpp
	src/SickMicroscan3.cpp
	src/ScanFilter.cpp
	src/UDP_Receiver.cpp
)

target_include_directories(pilot_sensors PUBLIC include generated/include)

target_link_libraries(pilot_sensors pilot_core)

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY generated/include/ DESTINATION include)
install(DIRECTORY modules/ DESTINATION interface/pilot/sensors)

install(TARGETS pilot_sensors DESTINATION lib)
