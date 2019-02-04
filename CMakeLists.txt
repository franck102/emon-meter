cmake_minimum_required(VERSION 3.9)
set(CMAKE_TOOLCHAIN_FILE ../Arduino.cmake)
#set(CMAKE_VERBOSE_MAKEFILE ON)
project(EmonMeter C CXX)

file(GLOB jeelib_src ../libraries/jeelib-master/*.cpp)

message(STATUS ${jeelib_src})
set(SOURCE_FILES
        EmonMeter.ino
        ${jeelib_src}
        Meter.h Meter.cpp
        PulseMeter.cpp PulseMeter.h Radio.cpp Radio.h TimeMeter.cpp TimeMeter.h)

set_source_files_properties(${SOURCE_FILES} PROPERTIES LANGUAGE CXX)

add_library(EmonMeter OBJECT ${SOURCE_FILES})
set_target_properties(EmonMeter PROPERTIES
        BOARD ATmega328P
        CLOCK 8MHz
        LINKER_LANGUAGE CXX)
target_compile_options(EmonMeter PUBLIC ${ARDUINO_FLAGS})
target_compile_definitions(EmonMeter PUBLIC ${ARDUINO_DEFS})

target_include_directories(EmonMeter PUBLIC
        .
        ../libraries/jeelib-RFxConsole-RSSI
        ${ARDUINO_INC}
        )

