cmake_minimum_required(VERSION 3.10)
project(ChatApp CXX)

if(NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "CMake toolchain file is required")
endif()
if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
endif()
find_package(Boost 1.70 REQUIRED COMPONENTS system date_time)

set(SERVER_SOURCES src/main_server.cpp)
set(CLIENT_SOURCES src/main_client.cpp)

add_executable(chat_server ${SERVER_SOURCES})

target_link_libraries(chat_server PRIVATE Boost::system Boost::date_time)
target_compile_features(chat_server PRIVATE cxx_std_17)

add_executable(chat_client ${CLIENT_SOURCES})

target_link_libraries(chat_client PRIVATE Boost::system Boost::date_time)
target_compile_features(chat_client PRIVATE cxx_std_17)