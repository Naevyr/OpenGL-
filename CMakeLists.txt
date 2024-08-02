cmake_minimum_required(VERSION 3.0.0)
project(opengl_plus VERSION 0.1.0 LANGUAGES CXX)
#set(CMAKE_GENERATOR_PLATFORM x64)
include(CTest)
enable_testing()
find_package(OpenGL REQUIRED)

add_subdirectory(lib/external/glfw)
add_subdirectory(lib/external/glad)
add_subdirectory(lib/external/glm)
add_subdirectory(lib/external/imgui-lib)

# Define MY_SOURCES to be a list of all the source files for my game 
file(GLOB_RECURSE LOCAL_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(opengl_plus ${LOCAL_SOURCES})

target_include_directories(opengl_plus PRIVATE lib/external)
target_include_directories(opengl_plus PRIVATE lib/external/glad/include)
target_include_directories(opengl_plus PRIVATE lib/external/glfw/include)

target_include_directories(opengl_plus PRIVATE lib/external/imgui-lib)
target_include_directories(opengl_plus PRIVATE lib/external/imgui-lib/imgui)
target_include_directories(opengl_plus PRIVATE src/)


target_link_libraries(opengl_plus glfw)
target_link_libraries(opengl_plus glad)
target_link_libraries(opengl_plus glm)
target_link_libraries(opengl_plus OpenGL::GL)
target_link_libraries(opengl_plus imgui)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_custom_command(TARGET opengl_plus PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:opengl_plus>/resources)