cmake_minimum_required(VERSION 3.22)
project(multithreading LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/main.cxx)
# target_link_libraries(${PROJECT_NAME} Threads)