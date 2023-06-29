cmake_minimum_required(VERSION 2.6)

file(GLOB GENERATED_SOURCE_FILES generated/src/*.cpp)

add_library(pilot_base_canopen SHARED
	${GENERATED_SOURCE_FILES}
	src/node_t.cpp
)

target_compile_options(pilot_base_canopen PUBLIC
	-Wall
	-Wno-switch
	-Wsuggest-override
)

target_include_directories(pilot_base_canopen PUBLIC
	generated/include
)

target_link_libraries(pilot_base_canopen
	pilot_base
)

install(DIRECTORY generated/include/ DESTINATION include)
install(DIRECTORY interface/ DESTINATION interface/pilot/base/canopen)
install(TARGETS pilot_base_canopen DESTINATION lib)


