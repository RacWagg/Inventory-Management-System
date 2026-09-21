cmake_minimum_required(VERSION 3.14)
project(InventoryManagementSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(INVENTORY_SOURCES
    src/Product.cpp
    src/Inventory.cpp
)

add_library(inventory_core ${INVENTORY_SOURCES})
target_include_directories(inventory_core PUBLIC include)

add_executable(inventory src/main.cpp)
target_link_libraries(inventory PRIVATE inventory_core)

enable_testing()

add_executable(inventory_tests tests/inventory_tests.cpp)
target_link_libraries(inventory_tests PRIVATE inventory_core)
add_test(NAME inventory_tests COMMAND inventory_tests)
