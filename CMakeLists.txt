cmake_minimum_required(VERSION 3.21)
project(main CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

add_subdirectory(raylib)

add_executable(${PROJECT_NAME}
main.cpp
functions.h functions.cpp
nicetea/nicetea.h nicetea/nicetea.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(PLATFORM STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

    target_link_options(${PROJECT_NAME} PRIVATE
        "-sUSE_GLFW=3"
        "-sASYNCIFY"
        "--shell-file" "${CMAKE_SOURCE_DIR}/raylib/src/minshell.html"
    )
elseif(PLATFORM STREQUAL "Desktop")
    if(WIN32)
        target_link_libraries(${PROJECT_NAME} PRIVATE winmm opengl32)
    endif()
endif()