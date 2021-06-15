cmake_minimum_required(VERSION 3.0.0)
project(pwhash VERSION 0.1.0)


set(SOURCES
    help.cpp
    clipcopy.c
    "list.cpp"
    new.cpp
    util.cpp
    main.cpp
    usepwd.cpp
)

add_compile_options(-g)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/headers ${CMAKE_CURRENT_LIST_DIR})
# target_precompile_headers(${PROJECT_NAME} ${HEAD})
add_subdirectory(password)
add_subdirectory(findconfdir)
target_link_libraries(${PROJECT_NAME} findconfdir password curses)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED TRUE)
