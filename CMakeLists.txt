cmake_minimum_required(VERSION 3.0.0)
project(Algorithms VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

#Простые сортировки
add_library(${PROJECT_NAME}_simple INTERFACE)
target_include_directories(${PROJECT_NAME}_simple INTERFACE ${CMAKE_SOURCE_DIR}/src/Simple)

#Сортировка Шелла
add_library(${PROJECT_NAME}_shell INTERFACE)
target_include_directories(${PROJECT_NAME}_shell INTERFACE ${CMAKE_SOURCE_DIR}/src/Shell)

#Быстрая сортировка
add_library(${PROJECT_NAME}_fast INTERFACE)
target_include_directories(${PROJECT_NAME}_fast INTERFACE ${CMAKE_SOURCE_DIR}/src/FastSort)

#Сортировка кучей
add_library(${PROJECT_NAME}_heap INTERFACE)
target_include_directories(${PROJECT_NAME}_heap INTERFACE ${CMAKE_SOURCE_DIR}/src/HeapSort)

#Стандартная сортировка
add_library(${PROJECT_NAME}_standart INTERFACE)
target_include_directories(${PROJECT_NAME}_standart INTERFACE ${CMAKE_SOURCE_DIR}/src/StandartSort)
#Исполняемый файл
add_executable(Algorithms src/main.cpp)
target_link_libraries(Algorithms PRIVATE ${PROJECT_NAME}_simple ${PROJECT_NAME}_shell ${PROJECT_NAME}_fast)
target_link_libraries(Algorithms PRIVATE ${PROJECT_NAME}_heap ${PROJECT_NAME}_standart)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
