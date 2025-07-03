cmake_minimum_required(VERSION 3.15.0)
project ("FreeRTOS TCP/IP Mayhem Harnesses" VERSION 1.0.0 LANGUAGES C)
include(FetchContent)

FetchContent_Declare( freertos_kernel
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
  GIT_TAG        main
)

FetchContent_Declare( freertos_plus_tcp
  GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Plus-TCP.git
  GIT_TAG        main
  GIT_SUBMODULES ""
)


add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM INTERFACE
    ConfigFiles
)


set( FREERTOS_PLUS_TCP_NETWORK_IF "POSIX" CACHE STRING "" FORCE)

FetchContent_MakeAvailable(freertos_kernel)
FetchContent_MakeAvailable(freertos_plus_tcp)

add_subdirectory(driver)
add_subdirectory(middleware)

# harnesses
add_subdirectory(harnesses/icmp)
