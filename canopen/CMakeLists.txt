cmake_minimum_required(VERSION 3.10)

file(GLOB GENERATED_SOURCE_FILES generated/src/*.cpp)

add_library(pilot_base_canopen SHARED
	${GENERATED_SOURCE_FILES}
	src/node_t.cpp
	src/CANopen_Proxy.cpp
)

target_compile_options(pilot_base_canopen PUBLIC
	-Wall
	-Wno-switch
	-Wsuggest-override
)

target_include_directories(pilot_base_canopen PUBLIC
	include
	generated/include
)

target_link_libraries(pilot_base_canopen
	pilot_base
)


add_executable(canopen_client
	src/client.cpp
)

target_link_libraries(canopen_client
	pilot_base_canopen
	pilot_base
)



install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY generated/include/ DESTINATION include)
install(DIRECTORY interface/ DESTINATION interface/pilot/base/canopen)
install(DIRECTORY modules/ DESTINATION interface/pilot/base/canopen)
install(TARGETS canopen_client DESTINATION bin)
install(TARGETS pilot_base_canopen DESTINATION lib)


