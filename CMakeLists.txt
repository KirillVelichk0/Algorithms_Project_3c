cmake_minimum_required(VERSION 3.0.0)
project(Algorithms VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

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

#Сортировка слиянием
add_library(${PROJECT_NAME}_merge INTERFACE)
target_include_directories(${PROJECT_NAME}_merge INTERFACE ${CMAKE_SOURCE_DIR}/src/MergeSort)

#Сортировка кучей
add_library(${PROJECT_NAME}_heap INTERFACE)
target_include_directories(${PROJECT_NAME}_heap INTERFACE ${CMAKE_SOURCE_DIR}/src/HeapSort)

#Стандартная сортировка
add_library(${PROJECT_NAME}_standart INTERFACE)
target_include_directories(${PROJECT_NAME}_standart INTERFACE ${CMAKE_SOURCE_DIR}/src/StandartSort)

#Поразрядная сортировка
add_library(${PROJECT_NAME}_radix INTERFACE)
target_include_directories(${PROJECT_NAME}_radix INTERFACE ${CMAKE_SOURCE_DIR}/src/RadixSort)

#Универсальный api для сортировок
set(MASTER_PATH ${CMAKE_SOURCE_DIR}/src/MasterSort)
add_library(${PROJECT_NAME}_master ${MASTER_PATH}/MasterSort.hpp ${MASTER_PATH}/MasterSort.cpp)
target_link_libraries(${PROJECT_NAME}_master PUBLIC ${PROJECT_NAME}_simple ${PROJECT_NAME}_shell ${PROJECT_NAME}_fast)
target_link_libraries(${PROJECT_NAME}_master PUBLIC ${PROJECT_NAME}_heap ${PROJECT_NAME}_standart ${PROJECT_NAME}_merge)
target_link_libraries(${PROJECT_NAME}_master PUBLIC ${PROJECT_NAME}_radix)

#Исполняемый файл
add_executable(Algorithms src/main.cpp)
target_link_libraries(Algorithms PRIVATE ${PROJECT_NAME}_simple ${PROJECT_NAME}_shell ${PROJECT_NAME}_fast)
target_link_libraries(Algorithms PRIVATE ${PROJECT_NAME}_heap ${PROJECT_NAME}_standart ${PROJECT_NAME}_merge)
target_link_libraries(Algorithms PRIVATE ${PROJECT_NAME}_radix ${PROJECT_NAME}_master)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
