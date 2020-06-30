cmake_minimum_required(VERSION 3.0.0)
project(cmake_cv VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(cmake_cv main.cpp operation.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(OpenCV REQUIRED)
target_link_libraries(cmake_cv ${OpenCV_LIBS})