cmake_minimum_required(VERSION 3.10)
project(pilot-base)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-DNOGDI)

file(GLOB GENERATED_SOURCE_FILES generated/src/*.cpp)

if(WIN32)
	list(APPEND PLATFORM_SOURCE_FILES
		src/win32/SerialPort.cpp
		src/win32/CAN_PeakUSB.cpp
	)
else()
	list(APPEND PLATFORM_SOURCE_FILES
		src/linux/SerialPort.cpp
		src/linux/CAN_Socket.cpp
	)
endif()

add_library(pilot_base SHARED
	${GENERATED_SOURCE_FILES}
	${PLATFORM_SOURCE_FILES}
	src/SerialPort.cpp
	src/CAN_Frame.cpp
	src/CAN_Proxy.cpp
	src/UDP_Socket.cpp
	src/NetworkStream.cpp
)

target_compile_options(pilot_base PUBLIC
	-pthread
)

target_include_directories(pilot_base PUBLIC include generated/include)

target_link_libraries(pilot_base vnx_base)
if(WIN32)
	target_link_libraries(pilot_base ws2_32)
endif()

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY generated/include/ DESTINATION include)
install(DIRECTORY modules/ DESTINATION interface/pilot/base)
install(DIRECTORY interface/ DESTINATION interface/pilot/base)
install(TARGETS pilot_base DESTINATION lib)

add_subdirectory(canopen)
