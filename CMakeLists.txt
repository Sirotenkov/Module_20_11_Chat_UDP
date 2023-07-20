cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(chat VERSION 1.0)

# add the executable
add_executable(chat main.cpp)
target_sources(chat PRIVATE chat.cpp sha1.cpp udp.cpp)
target_include_directories(chat PRIVATE ./)

if(WIN32)
  add_compile_definitions(_WINSOCK_DEPRECATED_NO_WARNINGS)
  target_link_libraries(chat wsock32 ws2_32)
endif()
