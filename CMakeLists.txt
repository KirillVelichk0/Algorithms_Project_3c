cmake_minimum_required(VERSION 3.0.0)
project(Algorithms VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

add_library(${PROJECT_NAME}_simple INTERFACE)
target_include_directories(${PROJECT_NAME}_simple INTERFACE ${CMAKE_SOURCE_DIR}/Simple)

add_executable(Algorithms main.cpp)
target_link_libraries(Algorithms PRIVATE ${PROJECT_NAME}_simple)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
