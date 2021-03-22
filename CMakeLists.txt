cmake_minimum_required(VERSION 3.0.0)
project(pwhash VERSION 0.1.0)


add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/headers)
add_subdirectory(pwdgen)
target_link_libraries(${PROJECT_NAME} pwdgen)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED TRUE)

