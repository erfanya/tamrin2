project(app)
set(CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.0)

set(SOURCES
    src/Main.cpp
    src/Customer.cpp
    src/Bank.cpp
    src/Time.cpp
)

include_directories(header)

add_executable(app ${SOURCES})
