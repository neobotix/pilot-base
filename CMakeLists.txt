cmake_minimum_required(VERSION 2.6)
project(pilot-base)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fPIC -pthread")
add_compile_options(-DNOGDI)

file(GLOB GENERATED_SOURCE_FILES generated/src/*.cpp)

if(WIN32)
	list(APPEND PLATFORM_SOURCE_FILES
		src/win32/SerialPort.cpp
		src/win32/UDP_Receiver.cpp
		src/win32/CAN_PeakUSB.cpp
	)
else()
	list(APPEND PLATFORM_SOURCE_FILES
		src/linux/SerialPort.cpp
		src/linux/UDP_Receiver.cpp
		src/linux/CAN_Socket.cpp
	)
endif()

add_library(pilot_base SHARED
	${GENERATED_SOURCE_FILES}
	${PLATFORM_SOURCE_FILES}
	src/SerialPort.cpp
	src/CAN_Frame.cpp
	src/CAN_Proxy.cpp
	src/UDP_Receiver.cpp
	src/UDP_Sender.cpp
	src/NetworkStream.cpp
)

target_include_directories(pilot_base PUBLIC include generated/include)

target_link_libraries(pilot_base vnx_base)
if(WIN32)
	#add_library(vnx_base STATIC IMPORTED)
	#set_target_properties(vnx_base PROPERTIES
	#	IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/dependencies/vnx/usr/lib/libvnx_base.dll.a
	#	INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/dependencies/vnx/usr/include
	#)
	target_link_libraries(pilot_base ws2_32)
endif()

install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY generated/include/ DESTINATION include)
install(DIRECTORY modules/ DESTINATION interface/pilot/base)
install(DIRECTORY interface/ DESTINATION interface/pilot/base)
install(TARGETS pilot_base DESTINATION lib)

add_subdirectory(canopen)
