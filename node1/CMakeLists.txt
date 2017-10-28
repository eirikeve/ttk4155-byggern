cmake_minimum_required(VERSION 3.5)


# MCU Options
set(MCU atmega162)
set(FOSC 4915200)
set(FREQUENCY_DIVIDER 1)
math(EXPR F_CPU "${FOSC} / ${FREQUENCY_DIVIDER}")
set(BAUD 9600)

# Programmer options
set(PROG_TYPE atmelice)
set(USBPORT usb)
set(BITCLOCK 1)
# Program names

set(AVRC     avr-gcc)
set(AVRCPP   avr-g++)
set(AVRSTRIP avr-strip)
set(OBJCOPY  avr-objcopy)
set(OBJDUMP  avr-objdump)
set(AVRSIZE  avr-size)
set(AVRDUDE  avrdude)

# Sets compiler
set(CMAKE_SYSTEM_NAME  Generic)
set(CMAKE_C_COMPILER   ${AVRC})
set(CMAKE_CXX_COMPILER ${AVRCPP})
set(CMAKE_ASM_COMPILER   ${AVRC})
project(node1 C CXX ASM)

# Important project paths
set(BASE_PATH    "${${PROJECT_NAME}_SOURCE_DIR}")
set(INC_PATH     "${BASE_PATH}/include")
set(SRC_PATH     "${BASE_PATH}/src")
set(LIB_DIR_PATH "${BASE_PATH}/lib")
set(BUILD_PATH   "${BASE_PATH}/build")
set(TEST_PATH    "${BASE_PATH}/test")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")

file(GLOB SRC_FILES "${SRC_PATH}/*.cpp" "${SRC_PATH}/*.c" "${SRC_PATH}/*.asm" "${TEST_PATH}/*.cpp" "${TEST_PATH}/*.c")
file(GLOB INC_FILES "${INC_PATH}/*.h" "${INC_PATH}/*.hpp" "${TEST_PATH}/*.h")
# file(GLOB TEST_SRC_FILES "${TEST_PATH}/*.cpp" "${TEST_PATH}/*.c")
# file(GLOB TEST_INC_FILES "${TEST_PATH}/*.h")


set(LIB_SRC_FILES)
set(LIB_INC_PATHS subdir ${LIBRARIES})
file(GLOB LIBRARIES "${LIB_DIR_PATH}/*")
foreach(subdir ${LIBRARIES})
    file(GLOB lib_src_files "${subdir}/*.c" "${subdir}/*.cpp" "${subdir}/*.asm")
    list(APPEND LIB_SRC_FILES "${lib_src_files}")
endforeach()

set(CSTANDARD "-std=c11")
set(CXXSTANDARD "-std=c++11")
set(CDEBUG    "-gstabs -g -ggdb")
set(CWARN     "-Wall -Wno-unknown-pragmas")
set(CONLYWARN "-Wstrict-prototypes")
set(CTUNING   "-funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -Wl,--gc-sections")
set(COPT      "-Os -lm -lprintf_flt")
set(ENABLE_SINGLETON "-fno-threadsafe-statics") # This isn't implemented in avr-g++ anyway, and without this singletons don't work...
set(DISABLE_EXCEPTIONS "-fno-exceptions") # This isn't implemented in avr-g++. Turn it off so the code doesn't try to cast an exception.
set(DEBUG_FLAG "-DDEBUG=${DEBUG}")
set(SAVE_SPACE_FLAG "-DSAVE_SPACE=${SAVE_SPACE}")
set(ADD_MAP "-Wl,-Map=${BUILD_PATH}/${PROJECT_NAME}.map")

set(CMCU      "-mmcu=${MCU}")
set(CDEFS     "-DF_CPU=${F_CPU} -DBAUD=${BAUD}")

set(CFLAGS   "${CDEBUG} ${SAVE_SPACE_FLAG} ${ADD_MAP} ${CMCU} ${COPT} ${CLINKER}  ${CWARN} ${CSTANDARD} ${CTUNING} ${CONLYWARN}")
set(CXXFLAGS "${CDEBUG} ${SAVE_SPACE_FLAG} ${ADD_MAP} ${CMCU} ${COPT} ${CLINKER}  ${CWARN} ${CXXSTANDARD} ${CTUNING} ${ENABLE_SINGLETON} ${DISABLE_EXCEPTIONS}")

set(CMAKE_C_FLAGS   "${CFLAGS}")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")
set(CMAKE_ASM_FLAGS   "${CFLAGS}")

# Project setup
include_directories(${INC_PATH} ${BASE_PATH} ${LIB_INC_PATHS} ${TEST_PATH})
add_executable(${PROJECT_NAME} ${SRC_FILES} ${LIB_SRC_FILES} ${TEST_PATH})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

# Defines
add_definitions(-DF_CPU=${F_CPU})
add_definitions(-DFOSC=${FOSC})
add_definitions(-DBAUD=${BAUD})
add_definitions(-DMCU_${MCU})

# Compiling targets
add_custom_target(strip ALL            ${AVRSTRIP} "${BUILD_PATH}/${PROJECT_NAME}.elf" DEPENDS ${PROJECT_NAME})
add_custom_target(hex   ALL            ${OBJCOPY} -R .eeprom -O ihex "${BUILD_PATH}/${PROJECT_NAME}.elf" "${BUILD_PATH}/${PROJECT_NAME}.hex" DEPENDS strip)
add_custom_target(flash                ${AVRDUDE} -c ${PROG_TYPE} -p ${MCU} -P ${USBPORT} -B ${BITCLOCK} -U flash:w:${BUILD_PATH}/${PROJECT_NAME}.hex:i DEPENDS hex)

set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${BUILD_PATH}/${PROJECT_NAME}.hex;${BUILD_PATH}/${PROJECT_NAME}.eeprom;${BUILD_PATH}/${PROJECT_NAME}.lst")