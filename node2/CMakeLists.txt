# Toolchain for AVR atmega 2560. Uses avr-libc and AVRDUDE.
# Thanks to Sondre Wangenstein Baugstø for help with debugging in the process of setting up the toolchain.

cmake_minimum_required(VERSION 3.5)

# High level options for toolchain
set(MCU atmega2560)
set(FOSC 16000000)
set(BAUD 9600)
set(PROG_TYPE wiring)
set(USBPORT /dev/ttyACM0)
set(BITCLOCK 115200)

# Set CPU frequency
math(EXPR F_CPU "${FOSC}")

# AVR compiler used
set(CMAKE_C_COMPILER    avr-gcc)
set(CMAKE_CXX_COMPILER   avr-g++)

# Rest of avr-libc needed to program the mcu
set(AVRSTRIP avr-strip)
set(OBJCOPY  avr-objcopy)
set(AVRDUDE  avrdude)

# Set project name
project(node2 C CXX)

# Set up paths needed
set(ROOT_PATH    "${${PROJECT_NAME}_SOURCE_DIR}") # Root path for project
set(SRC_PATH     "${ROOT_PATH}/src") # Src path
set(LIB_PATH "${ROOT_PATH}/lib") # path to library files
set(TEST_PATH    "${ROOT_PATH}/test") # Module tests
set(BUILD_PATH   "${ROOT_PATH}/build") # Output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")

# Set up files to be compiler under node2
file(GLOB SRC_FILES "${SRC_PATH}/*.c" "${SRC_PATH}/*.cpp" "${TEST_PATH}/*.cpp" "${TEST_PATH}/*.c")
file(GLOB INC_FILES "${TEST_PATH}/*.h")

# Files in lib
set(LIB_FILES)
set(LIB_INC_PATHS dir ${LIBRARIES})
file(GLOB LIBRARIES "${LIB_PATH}/*")
foreach(dir ${LIBRARIES})
    file(GLOB lib_files "${dir}/*.c" "${dir}/*.cpp")
    list(APPEND LIB_FILES "${lib_files}")
endforeach()

# Compiler flags
set(COMMON_FLAGS  "-mmcu=${MCU} -DF_CPU=${F_CPU} -DBAUD=${BAUD} -gstabs -g -ggdb -Wl,-Map=${BUILD_PATH}/${PROJECT_NAME}.map -Os -lm -lprintf_flt -Wall -Wno-unknown-pragmas -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections")
set(C_FLAGS       "-std=gnu11 -Wstrict-prototypes")
set(CPP_FLAGS     "-std=c++11 -fno-threadsafe-statics -fno-exceptions")

set(CMAKE_C_FLAGS   "${COMMON_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} ${CPP_FLAGS}")

# Project setup
include_directories(${ROOT_PATH} ${LIB_INC_PATHS} ${TEST_PATH})
add_executable(${PROJECT_NAME} ${SRC_FILES} ${LIB_FILES} ${TEST_PATH})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

# Defines
add_definitions(-DF_CPU=${F_CPU})
add_definitions(-DFOSC=${FOSC})
add_definitions(-DBAUD=${BAUD})
add_definitions(-DMCU_${MCU})

# Options to program the mcu
add_custom_target(strip ALL     ${AVRSTRIP} "${BUILD_PATH}/${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
add_custom_target(hex   ALL     ${OBJCOPY} -R .eeprom -O ihex "${BUILD_PATH}/${PROJECT_NAME}.elf" "${BUILD_PATH}/${PROJECT_NAME}.hex" DEPENDS strip)
add_custom_target(flash         ${AVRDUDE} -c ${PROG_TYPE} -p ${MCU} -D -P ${USBPORT} -b ${BITCLOCK} -U flash:w:${BUILD_PATH}/${PROJECT_NAME}.hex DEPENDS hex)
